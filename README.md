# VyuhaOne

> *A hybrid C++/Python AlphaZero-style chess engine built for high-throughput self-play and deep reinforcement learning.*

## Purpose
VyuhaOne is a modern chess engine designed to combine high-performance C++ tree search with flexible PyTorch deep reinforcement learning. It explores zero-knowledge self-play learning (AlphaZero paradigm) while maintaining cross-platform compatibility across macOS and Windows.

## Architectural Principles
1. 1. **Performance where it counts:** Board-state operations, legal move generation, and tree-search infrastructure are implemented in C++ to minimise runtime overhead and enable careful control over memory layout..
2. **Experimentation-friendly:** Neural network models, training loops, and loss functions remain 100% Pythonic for rapid AI iteration.
3. **Efficient data interchange:** Board features and neural-network inputs will use explicitly documented contiguous memory layouts, with copying minimised where correctness and ownership rules permit.
4. **Cross-Platform Parity:** Clean CMake builds compile seamlessly on Apple Silicon (Clang) and Windows (MSVC).

## Language Responsibilities

| Subsystem | Language | Purpose |
| :--- | :--- | :--- |
| **Board State & Rules** | C++20 | Fast move generation, FEN parsing, and state bitboards. |
| **MCTS Search Engine** | C++20 | Multithreaded tree expansion and PUCT action selection. |
| **Bindings Layer** | C++ / pybind11 | Zero-copy memory bridge between C++ structs and PyTorch Tensors. |
| **Neural Network** | Python / PyTorch | Dual-Head ResNet (Policy & Value predictions). |
| **Trainer Pipeline** | Python | Self-play replay buffer management, loss functions, and optimization. |

## Supported Platforms
* **macOS:** Apple Silicon (M1/M2/M3/M4/M5) and Intel via Clang / Xcode CLI.
* **Windows:** Windows 10/11 (x64) via MSVC (Visual Studio 2022 / Build Tools).

## Repository Structure
VyuhaOne/
├── CMakeLists.txt
├── CMakePresets.json
├── pyproject.toml
├── README.md
├── engine/
│   ├── include/vyuhaone/
│   └── src/
├── apps/
│   └── uci/
├── bindings/
│   └── python/
├── python/
│   └── vyuhaone/
├── tests/
│   ├── cpp/
│   └── python/
└── docs/
    └── decisions/