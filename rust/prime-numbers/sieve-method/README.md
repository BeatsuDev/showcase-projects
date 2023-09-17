# Finding prime numbers up to 100_000_000
The sieve method uses the prime sieve of eratosthenes' method to find all primes up to 100 million.
This is the fastest method of finding primes of all the algorithms in this repository.

To run the application:
```
cargo run
```

### Speeding up the program
You can expect up to 5x - 10x speed improvements or more if you build the application with optimizations first.

```
cargo build --release
"target/release/primes-sieve.exe"
```