# ADR-0001: C++ and Python Responsibility Boundary

## Status
Accepted

## Context
VyuhaOne requires high computational throughput for Monte Carlo Tree Search (MCTS) rollout loops, but needs rapid iteration, dynamic model experimentation, and rich ecosystem access for deep learning training routines.

## Decision
We adopt a **Hybrid C++/Python Model** connected via `pybind11`.

* **What belongs in C++?**
  * **Chess Engine & Game Logic:** Board state bitboards, legal move generation, move application, and checkmate/draw evaluation.
  * **Tree Search Infrastructure:** MCTS node allocation, parent/child traversals, and PUCT selection algorithms.
  * **Batching Queue:** Aggregating tensor inference requests from concurrent self-play search threads into unified batches.

* **What belongs in Python?**
  * **Neural Architecture:** Dual-head ResNet / Transformer definitions using raw PyTorch (`torch.nn.Module`).
  * **Training Orchestration:** Optimizer steps, loss calculations (cross-entropy + MSE), learning rate scheduling, and checkpoint savings.
  * **Dataset Handling:** Replay buffer management, dataset serialization, and data augmentation.

* **How may they communicate?**
  * C++ exposes board state structures, move indexers, and MCTS search managers to Python via `pybind11`.
  * Python passes PyTorch Tensor pointers (`torch::Tensor`) across the boundary into C++ without copying memory (zero-copy via NumPy/C++ buffer protocols).

## Alternatives Considered
* **Pure C++:** Maximum performance, but extremely slow iteration speed for neural network experimentation and loss tweaking.
* **Pure Python:** Excellent for model building, but MCTS tree traversals run 10x-100x slower due to Python object overhead and Global Interpreter Lock (GIL) limitations.
* **Python Engine with C++ Optimization Modules:** Keeping search in Python and calling C++ only for movegen creates high boundary-crossing overhead during millions of node visits.

## Consequences
* **What becomes easier?**
  * MCTS search runs at thousands of evaluations per second in compiled native code.
  * Neural network designs can be swapped or modified in Python in seconds without re-compiling C++ cores.
* **What becomes harder?**
  * Cross-platform build configuration (CMake + MSVC/Clang + pybind11) requires maintenance across Windows and macOS.
* **What new failure modes are introduced?**
  * Memory leaks across the Python/C++ boundary if memory ownership of tensors/nodes isn't managed strictly.
  * GIL (Global Interpreter Lock) contention when C++ threads request neural evaluations from Python.