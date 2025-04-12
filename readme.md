# Mandelbrot Set Optimization Analysis

![Mandelbrot Set](images/mandelbrot_set.png)

The **Mandelbrot set** is a famous fractal defined as the set of complex numbers \( c \) for which the iterative sequence:

\[
z_{n+1} = z_n^2 + c \quad (\text{where} \ z_0 = 0)
\]

does not diverge to infinity. When visualized, it produces intricate, infinitely detailed fractal patterns.

## Computational Complexity

Generating the Mandelbrot set is computationally expensive because:

- Each pixel requires dozens to hundreds of complex-number iterations.
- The algorithm must check whether \( |z_n| < 2 \) (escape condition) in every iteration.
- The color of a pixel depends on how quickly the sequence escapes (if it does).

This repository contains three implementations of Mandelbrot set generation with different optimization levels: Naive implementation, SIMD-like optimization, ARM NEON Intrinsics implementation

## ⚙️ Architecture & Requirements

This project includes **two implementations** of Mandelbrot rendering:

| Version             | Target Architecture | Instruction Set        |
|---------------------|---------------------|------------------------|
| Scalar (naive)      | x86, ARM            | None (portable)        |
| SIMD (optimized)    | ARM64 (e.g., M1/M2) | NEON Intrinsics        |


# Performance Analysis

The implementation shows linear scaling with iteration count:

(images/analysis.png)

Average time per iteration(naive): 114.20 ms
Average time per iteration(optimized): 36.52 ms

The NEON-optimized version demonstrates a 3.12x speedup over the naive scalar implementation.



