# Task
### Task 1:
[Josephus' problem](https://en.wikipedia.org/wiki/Josephus_problem)

### Task 2:
Parse text files and find matching brackets () {} and []. Return if a file is valid or not (has a closing bracket for each open bracket
and in the correct order). The program should be able to read and validate source code files of languages that use brackets.

## Time complexity
My solution is Θ(n).

## Notes
The error messages output the char code as a u8. For example, ( = 40. ) = 41. \[ = 91, \] = 93.

Simplest way to install zig is through a package manager:
https://github.com/ziglang/zig/wiki/Install-Zig-from-a-Package-Manager

Other ways of installing zig: https://ziglang.org/learn/getting-started/

For ubuntu:  

    sudo apt-get update && sudo apt install snap && sudo snap install zig --classic

For Arch: 

    pacman -S zig
