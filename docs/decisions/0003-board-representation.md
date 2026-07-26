# ADR-0003: Board and Position Representation

## Status
Proposed

## Context
Describe what information a chess position must contain and why performance matters for MCTS and self-play.

## Proposed decision
- 64-bit bitboards
- Square mapping
- Piece and colour indexing
- Cached occupancy
- Historical state

## Alternatives considered
- 8×8 array
- Mailbox
- 0x88
- Pure bitboards
- Hybrid bitboards plus piece-on-square array

## Invariants
State equations that must always hold.

## Open questions
- Hybrid piece array?
- Copy versus make/unmake?
- Incremental versus recomputed occupancy?