# E-Commerce Order Sorting Engine

A high-throughput transactional sorting engine designed for enterprise logistics. [cite_start]Developed by **Tilak M K** at The National Institute of Engineering, this system implements a stable Divide and Conquer architecture (Merge Sort) to process massive, unsorted order sequences[cite: 78, 79].

## System Architecture
The application relies on structural multi-attribute sorting to strictly satisfy commercial delivery SLAs. [cite_start]Primitive quadratic frameworks like Bubble or Selection Sort were rejected due to catastrophic worst-case degradation ($O(n^2)$)[cite: 81, 740]. 

This system guarantees:
* [cite_start]**Strict Performance:** $O(n \log n)$ runtime across all permutations[cite: 123].
* [cite_start]**Positional Stability:** Preserves initial FIFO temporal tracking for identical keys[cite: 124, 718].
* [cite_start]**Enterprise Hierarchies:** 1. *Priority Routing:* Premium Status $\rightarrow$ Priority $\rightarrow$ Pincode[cite: 135, 268].
  2. [cite_start]*Chronological Routing:* Premium Status $\rightarrow$ Priority $\rightarrow$ Order Date $\rightarrow$ Pincode[cite: 286].

## Installation & Compilation

1. Ensure you have `gcc` and `make` installed.
2. Clone the repository and navigate to the root directory.
3. Compile the project using the provided Makefile:
   ```bash
   make
   ```

4. Run the engine:
   ```bash
   ./build/ecommerce_engine
   ```
