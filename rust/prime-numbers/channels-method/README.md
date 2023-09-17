# Finding prime numbers in a range, using rust channels
To run the application:
```
cargo run -- --start <start range> --end <end range> --threads <thread count> --print-results <1 or 0>
```

start: Start range

end: End range

threads: Amount of threads to use

print_results: Whether to print the prime numbers found immediately once they have been found. 1 = True, 0 = False.

### Speeding up the program
You can expect up to 5x - 10x speed improvements or more if you build the application with optimizations first. Also
note that writing to stdout is very slow.

```
cargo build --release
target/release/primes-channels-threads.exe -s <start range> -e <end range> -t <thread count> -p <1 or 0>
```
