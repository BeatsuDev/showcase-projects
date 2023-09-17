use std::time::{Duration, Instant};
use std::thread;
use std::cmp;
extern crate num_cpus;

fn main() {
    let cutoff: u64 = 10_000_000;

    let start: Instant = Instant::now();
    let primes = primes(cutoff, num_cpus::get());
    let duration: Duration = start.elapsed();

    println!("Found {} primes from 0 to {} in {:?}!", primes.len(), cutoff, duration);
}

fn primes(n: u64, threads: usize) -> Vec<u64> {
    if n < 2 { return vec![]; }
    if n == 2 { return vec![2]; }
    
    let mut primes = vec![2, 3];
    let mut thread_objects = vec![];

    let segment_size = (((n - 5) as f64) / (threads as f64)).ceil() as u64;

    for i in 0..threads as u64 {
        let start: u64 = 5 + i*segment_size;
        let end: u64 = cmp::min(5 + (i+1)*segment_size, n + 1);

        println!("Thread {}, segment: {} - {}", i, start, end);

        thread_objects.push(thread::spawn(move || {
            let start_time: Instant = Instant::now();
            let result = (start..end).filter(is_prime).collect();
            let duration: Duration = start_time.elapsed();
            println!("Thread {} used {:?}", i, duration);
            return result
        }));
    }

    for thread in thread_objects {
        let result: Vec<u64> = thread.join().unwrap();
        primes.extend(result);
    }

    return primes;
}

fn is_prime(n: &u64) -> bool {
    if *n <= 1 { return false; }
    let upper_bound = ((*n) as f64).sqrt().ceil() as u64 + 1;
    for a in 2..upper_bound {
        if n % a == 0 { return false; }
    }
    return true;
}