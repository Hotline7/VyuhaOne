# VyuhaOne

> *A hybrid C++/Python AlphaZero-style chess engine built for high-throughput self-play and deep reinforcement learning.*

## Purpose
VyuhaOne is a modern chess engine designed to combine high-performance C++ tree search with flexible PyTorch deep reinforcement learning. It explores zero-knowledge self-play learning (AlphaZero paradigm) while maintaining cross-platform compatibility across macOS and Windows.

## Architectural Principles
1. **Performance where it counts:** Game tree evaluation and board state mutations are zero-cost operations handled natively in C++.
2. **Experimentation-friendly:** Neural network models, training loops, and loss functions remain 100% Pythonic for rapid AI iteration.
3. **Zero-Copy Tensor Flow:** C++ search operations pack board representations directly into memory layouts readable by PyTorch tensors without memory allocation overhead.
4. **Cross-Platform Parity:** Clean CMake builds compile seamlessly on Apple Silicon (Clang) and Windows (MSVC).

## Language Responsibilities

| Subsystem | Language | Purpose |
| :--- | :--- | :--- |
| **Board State & Rules** | C++17 | Fast move generation, FEN parsing, and state bitboards. |
| **MCTS Search Engine** | C++17 | Multithreaded tree expansion and PUCT action selection. |
| **Bindings Layer** | C++ / pybind11 | Zero-copy memory bridge between C++ structs and PyTorch Tensors. |
| **Neural Network** | Python / PyTorch | Dual-Head ResNet (Policy & Value predictions). |
| **Trainer Pipeline** | Python | Self-play replay buffer management, loss functions, and optimization. |

## Supported Platforms
* **macOS:** Apple Silicon (M1/M2/M3/M4) and Intel via Clang / Xcode CLI.
* **Windows:** Windows 10/11 (x64) via MSVC (Visual Studio 2022 / Build Tools).

## Repository Structure
```text
VyuhaOne/
├── CMakeLists.txt           # Cross-platform CMake configuration
├── pyproject.toml           # Python build pipeline (scikit-build-core)
├── docs/                    # Architecture Decision Records (ADRs)
├── src/
│   ├── cpp/                 # C++ Core (Board logic, MCTS, pybind11 exports)
│   └── vyuhaone/            # Python Package (PyTorch architecture, training loops)
└── tests/                   # Pytest integration tests & C++ unit tests