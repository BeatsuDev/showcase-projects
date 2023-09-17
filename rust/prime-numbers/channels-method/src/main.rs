#![allow(unused)]
use clap::Parser;
use std::thread;
use std::time::{Duration, Instant};
use std::sync::{Mutex, Arc};
use crossbeam_channel::{unbounded, Sender, Receiver};


/// Search for a pattern in a file and display the lines that contain it.
#[derive(Parser)]
#[command(author, version, about, long_about = None)]
struct CLI {
    #[arg(short, long, default_value_t=1)]
    start: usize,
    #[arg(short, long)]
    end: usize,
    #[arg(short, long)]
    threads: usize,
    #[arg(short, long, default_value_t=0)]
    print_results: usize,
}

fn main() {
    let args = CLI::parse();
    println!("Calculating primes from {} to {} with {} threads!", args.start, args.end, args.threads);

    let start: Instant = Instant::now();
    let primes = primes(args.start, args.end, args.threads, args.print_results != 0);
    let duration: Duration = start.elapsed();

    println!("Found {} primes in {:?}!", primes.len(), duration);
}

fn primes(start: usize, end: usize, threads: usize, print_results: bool) -> Vec<usize> {
    let mut prime_numbers: Vec<usize> = vec![];
    if start < 2 && end > 2 { prime_numbers.push(2); }

    let numbers_to_process: Vec<usize>;
    if start % 2 == 0 {
        numbers_to_process = (start+1..=end).step_by(2).collect();
    } else {
        numbers_to_process = (start..=end).step_by(2).collect();
    }

    // Create 2 channels. One for sending numbers to be processed
    // One for sending prime numbers back
    let (sender, receiver): (Sender<usize>, Receiver<usize>) = unbounded();
    let (sender2, receiver2): (Sender<usize>, Receiver<usize>) = unbounded();

    let mut spawned_threads = vec![];

    // Create threads to process prime numbers
    for i in 0..threads {
        let number_receiver = receiver.clone();
        let prime_sender = sender2.clone();

        let spawned_thread = thread::spawn(move || {
            // Receive numbers for processing
            let mut data = number_receiver.recv();
            while data.unwrap() > 0 {
                // Send the number to the prime_number channel if it's a prime number
                if is_prime(data.unwrap()) {
                    prime_sender.send(data.unwrap());
                }
                data = number_receiver.recv();
            }
            // Send a code 0 when the thread has finished.
            prime_sender.send(0);
        });
        spawned_threads.push(spawned_thread);
    }

    // Send all the numbers that are to be processed to the channel
    for number in numbers_to_process {
        sender.send(number);
    }

    // Send the stop signal after all numbers to be processed have been sent
    for i in 0..threads {
        sender.send(0);
    }

    // When a thread is finished, it sends back a 0. Count that all threads have finished
    // Then we know that we have all the prime numbers
    let mut threads_finished = 0; 
    while threads_finished < threads {
        let received_num = receiver2.recv().unwrap();
        if (print_results && received_num != 0) {
            println!("{}", received_num);
        }
        if received_num == 0 {
            threads_finished += 1;
        } else {
            prime_numbers.push(received_num);
        }
    }

    // Join all threads
    for thread in spawned_threads {
        thread.join();
    }

    return prime_numbers;
}

fn is_prime(n: usize) -> bool {
    if n < 2 { return false; }
    if n == 2 { return true; }
    for i in 2..((n as f64).sqrt().ceil() as usize + 1) {
        if n % i == 0 { return false; }
    }
    return true;
}