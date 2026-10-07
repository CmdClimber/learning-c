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
Each exercise is organized into its own directory to keep the code modular and self-contained.


```
.
├── stack_direction/         # Detecting stack growth direction
│   ├── README.md            # Theory: Recursion, inline attributes, volatile
│   └── main.c               # Implementation of 4 different detection methods
│
├── byte_swap/               # Endianness conversion strategies
│   ├── README.md            # Theory: Bitwise ops, unions, builtin functions
│   └── main.c               # Comparison of 5 byte-swapping algorithms
│
├── uart_fifo/               # Simulated UART driver with Ring Buffer
│   ├── README.md            # Theory: Interrupts, FIFO buffers, state machines
│   ├── uart.h               # UART interface and register definitions
│   ├── uart.c               # UART implementation (buffer management)
│   └── main.c               # Test driver simulating TX/RX interrupts
│
├── matrix_ops/              # Matrix transformation techniques
|   ├── README.md            # Theory: Cache locality, pointer arithmetic
|   ├── matrix.h             # Matrix structure and function prototypes
|   ├── matrix.c             # Various transpose/rotate implementations
|   └── main.c               # Benchmark runner and verification tests
└── ...
```
    
## 📄 File Legend
| File | Description |
|------|-------------|
| `README.md` | Theoretical background, educational notes, and specific compilation instructions for the exercise. |
| `main.c` | The entry point. Contains all implementation variants, test cases, and benchmark runners. |
| `*.h` / `*.c` | Optional modular files. Used when the logic is split into interfaces (header) and implementations (source). |

## 🛠️ Building & Running
All exercises are written in standard C99/C11 and can be compiled with gcc or clang.

### Compile with debugging symbols
 `gcc -g -O0 exercise.c -o exercise` 

### Compile with optimization
 `gcc -O2 exercise.c -o exercise` 

# Run
./exercise

## 📚 Educational Focus
> *"F.A.I.L. - First Attemp In Learning"*


Although code should ideally be easy to read, self-documenting, and consistent, these files are widely commented to help you understand the complexity, richness, and different frameworks involved in low-level programming.

Each exercise is designed to teach through comparison and experimentation:

- **Multiple Implementations**  
  From naive approaches to highly optimized solutions. See how different algorithms solve the same problem and why one might be preferred over another.

- **Compiler Analysis**  
  Use tools like `objdump` or `gdb` to inspect the generated assembly code. Understand exactly what your compiler does with your C code under different optimization levels (`-O0`, `-O2`).

- **Portability Checks**  
  Test your code on different architectures (x86, ARM) and compilers (GCC, Clang, MSVC). Learn which constructs are portable and which depend on specific hardware behavior.

- **Debugging Practice**  
  Step through pointer arithmetic and buffer boundaries in `gdb`. Watch segmentation faults happen, then learn to read the assembly that caused them. Use `valgrind` to detect memory leaks and invalid reads/writes.

## 🤝 Contributing
This is a personal learning journal, but if you spot a bug or have a better optimization strategy feel free to contact me, open an issue or pull request!

Built with ❤️ and C pointers.
