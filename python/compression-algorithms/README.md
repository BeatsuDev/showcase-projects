# Task 8 in Algorithms and Datastructures 2023
Run the solution on linux with:

```
mv run.txt run.sh && chmod u+x run.sh && ./run.sh
```

Task: Create a compression algorithm that successfully reduces the file size and can losslessly
decompress the file again.

My solution reduces the file size of the given file `diverse.lyx` to 6.75% of original size
by first using the Lempel-Ziv 1977 (LZ77) Compression algorithm, then using huffman coding 
with two huffman trees; one for single bytes and one for groups of three bytes.

I wrote a medium post when solving this task:
https://ericbie.medium.com/never-struggle-with-beginning-coding-projects-again-57496bcee2b1
