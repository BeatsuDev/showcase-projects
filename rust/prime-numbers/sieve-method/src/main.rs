use std::time::Instant;

fn main() {
    let cutoff: u32 = 100_000_000;

    let start = Instant::now();
    let primes = prime_sieve(cutoff);
    let duration = start.elapsed();

    println!("Found {} primes from 0 to {} in {:?}!", primes.len(), cutoff, duration);
}

fn prime_sieve(cutoff: u32) -> Vec<u32> {
    // Create a vector of booleans representing the numbers from 0 to cutoff
    let mut primes_bools: Vec<bool> = vec![true; cutoff as usize];

    // 0 and 1 are not prime numbers
    primes_bools[0] = false;
    primes_bools[1] = false;

    // The maximum value to remove multiples of a prime number
    let max_remove: u32 = (cutoff as f32).sqrt() as u32;

    // Iterate through the numbers from 2 to max_remove
    for n in 2..=max_remove {
        if !primes_bools[n as usize] { continue; }

        // Remove the multiples of the current number
        for multiple in (n*n..cutoff).step_by(n as usize) {
            primes_bools[multiple as usize] = false;
        }
    }

    // Convert list of booleans to vector of actual prime numbers
    primes_bools
        .into_iter()
        .enumerate()
        .filter_map(|(i, is_prime)| if is_prime { Some(i as u32) } else { None })
        .collect()
}