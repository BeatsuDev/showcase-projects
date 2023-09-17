# Finding prime numbers up to 10_000_000
The weighted segments method uses multiple threads which each check a seperate number range for prime numbers.
The number ranges (called segments) are larger for lower numbers and lower for higher numbers - in an attempt
to balance the workload. 

The weighting / distribution was found by experimenting and is optimized for n = 10_000_000

To run the application:
```
cargo run
```

### Speeding up the program
You can expect up to 5x - 10x speed improvements or more if you build the application with optimizations first.

```
cargo build --release
"target/release/primes-threads.exe"
```