# Learning C: From Software to Hardware

> *"Understanding how hardware cooperates with software makes you a better coder."*

This project documents my personal journey into **low-level programming** and **embedded systems**. 

In the embedded world, you cannot hide behind abstractions. You need to understand memory, pointers, registers, and the hardware itself. This repository contains:

- **Educational Exercises**: Classic C problems reimagined for hardware contexts.
- **Pattern Implementations**: Solutions to common embedded challenges (UART, I2C, DMA).
- **Performance Comparisons**: Benchmarking different approaches to see how compilers optimize code.

## 🚀 Why This Project?

I strongly believe that mastering the fundamentals of C is the key to unlocking the embedded world. By stripping away high-level frameworks, we gain visibility into:
- **Memory Management**: How data is stored, accessed, and optimized.
- **Hardware Interaction**: Simulating registers, interrupts, and bus protocols.
- **Compiler Behavior**: How optimization flags (`-O0` vs `-O2`) change binary output.

## 📂 Project Structure


## 🛠️ Building & Running
All exercises are written in standard C99/C11 and can be compiled with gcc or clang.

### Compile with debugging symbols
gcc -g -O0 exercise.c -o exercise

### Compile with optimization
gcc -O2 exercise.c -o exercise

# Run
./exercise

## 📚 Educational Focus
Each exercise includes:

Multiple Implementations: From naive to optimized.
Compiler Analysis: Using objdump or gdb to inspect assembly.
Portability Checks: Testing on different architectures (x86, ARM).

## 🤝 Contributing
This is a personal learning journal, but if you spot a bug or have a better optimization strategy feel free to contact me, open an issue or pull request!

Built with ❤️ and C pointers.
