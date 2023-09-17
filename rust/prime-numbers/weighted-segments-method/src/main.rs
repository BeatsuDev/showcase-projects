use std::time::{Duration, Instant};
use std::thread;
use std::cmp;
extern crate num_cpus;

fn main() {
    let cutoff: usize = 10_000_000;

    let start: Instant = Instant::now();
    let primes = primes(cutoff, num_cpus::get());
    let duration: Duration = start.elapsed();

    println!("Found {} primes from 0 to {} in {:?}!", primes.len(), cutoff, duration);
}

fn primes(n: usize, threads: usize) -> Vec<usize> {
    if n < 2 { return vec![]; }
    if n == 2 { return vec![2]; }
    
    let mut primes = vec![2, 3];
    let mut thread_objects = vec![];

    let segment_size: usize = (((n - 5) as f64) / (threads as f64)).ceil() as usize;

    // Create the adjusted segment lengths
    let mut segments = vec![segment_size; threads];

    for i in 0..=(threads/2) {
        let adjustment = segment_size / (3.14159_f32).powf((i+1) as f32) as usize;
        segments[i] += adjustment;
        let index_from_back = segments.len() - (i+1);
        segments[index_from_back] -= adjustment;
    }

    // Calculate start values
    let mut starts = vec![];

    let mut temp_start = 5;
    for segment_length in &segments {
        starts.push(temp_start);
        temp_start += *segment_length;
    }
    
    // Run threads
    for i in 0..threads {
        let start: usize = starts[i];
        let end: usize = cmp::min(starts[i] + segments[i], n + 1);

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
        let result: Vec<usize> = thread.join().unwrap();
        primes.extend(result);
    }

    return primes;
}

fn is_prime(n: &usize) -> bool {
    if *n <= 1 { return false; }
    let upper_bound = ((*n) as f64).sqrt().ceil() as usize + 1;
    for a in 2..upper_bound {
        if n % a == 0 { return false; }
    }
    return true;
}