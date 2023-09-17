# Finding prime numbers up to 10_000_000
The threads method uses multiple threads which each check a seperate number range for prime numbers.

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