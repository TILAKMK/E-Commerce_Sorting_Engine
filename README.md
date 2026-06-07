# E-Commerce Order Sorting Engine

A high-throughput transactional sorting engine designed for enterprise logistics. This system implements a stable Divide and Conquer architecture (Merge Sort) to process massive, unsorted order sequences.

## System Architecture

The application relies on structural multi-attribute sorting to strictly satisfy commercial delivery SLAs. Primitive quadratic frameworks like Bubble or Selection Sort were rejected due to catastrophic worst-case degradation ($O(n^2)$). 

This system guarantees:
* **Strict Performance:** $O(n \log n)$ runtime across all permutations.
* **Positional Stability:** Preserves initial FIFO temporal tracking for identical keys.
* **Enterprise Hierarchies:** 1. *Priority Routing:* Premium Status $\rightarrow$ Priority $\rightarrow$ Pincode.
  2. *Chronological Routing:* Premium Status $\rightarrow$ Priority $\rightarrow$ Order Date $\rightarrow$ Pincode.

## Installation & Compilation

1. Ensure you have `gcc` and `make` installed on your system.
2. Clone the repository and navigate to the root directory.
3. Compile the project using the provided Makefile:
   ```bash
   make
