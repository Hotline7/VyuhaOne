# ADR-0001: C++ and Python Responsibility Boundary

## Status
Accepted

## Context
VyuhaOne requires high computational throughput for MCTS tree traversal, expansion, backup, and batched neural-network evaluation.

## Decision
I adopted a **Hybrid C++/Python Model** connected via `pybind11`.

* **What belongs in C++?**
  * **Chess Engine & Game Logic:** Board state bitboards, legal move generation, move application, and checkmate/draw evaluation.
  * **Tree Search Infrastructure:** MCTS node allocation, parent/child traversals, and PUCT selection algorithms.
  * **Batching Queue:** Aggregating tensor inference requests from concurrent self-play search threads into unified batches.

* **What belongs in Python?**
  * **Neural Architecture:** Dual-head ResNet / Transformer definitions using raw PyTorch (`torch.nn.Module`).
  * **Training Orchestration:** Optimiser steps, loss calculations (cross-entropy + MSE), learning rate scheduling, and checkpoint savings.
  * **Dataset Handling:** Replay buffer management, dataset serialization, and data augmentation.

* **How may they communicate?**
  * C++ exposes chess-state operations and search interfaces through a narrow binding layer.
  * Data exchanged across the boundary must use documented ownership, lifetime, shape, type, and memory-layout rules.
  * The precise tensor-interchange mechanism will be selected after evaluating pybind11 buffers, NumPy interoperability, DLPack, and PyTorch C++ extensions.

## Alternatives Considered
* **Pure C++:** Maximum performance, but extremely slow iteration speed for neural network experimentation and loss tweaking.
* **Pure Python:** Simplifies development, but interpreter overhead, object allocation, and GIL constraints may limit high-throughput tree traversal. This must be measured using project-specific benchmarks.
* **Python Engine with C++ Optimization Modules:** Keeping search in Python and calling C++ only for movegen creates high boundary-crossing overhead during millions of node visits.

## Consequences
* **What becomes easier?**
  * Native search infrastructure provides the opportunity for high-throughput execution and controlled memory management, subject to benchmarking.
  * Neural network designs can be swapped or modified in Python in seconds without re-compiling C++ cores.
* **What becomes harder?**
  * Cross-platform build configuration (CMake + MSVC/Clang + pybind11) requires maintenance across Windows and macOS.
* **What new failure modes are introduced?**
  * Memory leaks across the Python/C++ boundary if memory ownership of tensors/nodes isn't managed strictly.
  * GIL (Global Interpreter Lock) contention when C++ threads request neural evaluations from Python.