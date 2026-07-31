## Milestone 0 — Repository Foundation

### What I built
I created the initial cross-platform repository structure, README, `.gitignore`, and the first Architecture Decision Record.

### Architectural decisions
The chess rules and search infrastructure will be implemented in C++, while Python will own neural-network experimentation and training orchestration. Communication will occur through a narrow binding layer with explicit memory-ownership rules.

### Challenges and uncertainties
I was initially unfamiliar with the role and format of `.gitignore`. I learned that it is a plain-text file that prevents generated, local, and machine-specific artefacts from being tracked by Git.

### Complexity and performance
No runtime algorithms have been implemented. Performance claims remain design goals and must later be validated through benchmarks.

### Open questions
- Exact Python/C++ tensor-interchange mechanism
- Testing framework
- Dependency-management strategy
- Ownership of neural-network inference batching




## Milestone 1 – Build System Foundation

### What I built
- Initial cross-platform repository structure.
- Engine library target.
- UCI executable target.
- Version API (`version.hpp` / `version.cpp`).
- Hierarchical CMake build system.

### Key architectural decisions
- Separate interface (.hpp) from implementation (.cpp).
- One CMakeLists per subsystem.
- Public headers under engine/include.
- Engine built as a reusable library.

### Biggest lessons
- Headers declare; source files define.
- Root CMake delegates to subsystem CMake files.
- IntelliSense diagnostics are not necessarily compiler diagnostics.
- Build systems have ownership boundaries just like software components.

### Issues encountered
- IntelliSense did not recognise compile definitions.
- Fixed by exporting compile commands and configuring VS Code.



## Milestone 2 – Bitboard Position Representation

### What I built
- Foundational engine types for colour, piece type, castling rights and bitboards.
- A1=0 through H8=63 square coordinate system.
- Read-only Position interface with private internal state.
- Empty default position and explicit StartingPosition factory.
- Cached colour and combined occupancies.
- GoogleTest and CTest infrastructure.

### Architectural decisions
- Use pure bitboards rather than a duplicated piece-on-square array.
- Treat piece bitboards as authoritative state and occupancies as derived caches.
- Restrict mutation to Position methods.
- Use an explicit StartingPosition factory rather than making it the default constructor.

### Invariants
- Each colour occupancy equals the OR of its six piece bitboards.
- Combined occupancy equals White occupancy OR Black occupancy.
- White and Black occupancies must not overlap.

### Issues encountered
- IntelliSense initially lacked CMake-generated include paths.
- The test directory was initially processed before GoogleTest was available.
- Solved by configuring FetchContent before adding tests/cpp and regenerating compile_commands.json.

### Verification
- Clean CMake build succeeded.
- Six GoogleTest cases passed through CTest.