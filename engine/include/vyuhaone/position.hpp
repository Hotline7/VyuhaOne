#pragma once

#include <array>
#include <cstdint>
#include <cstddef>
#include "vyuhaone/types.hpp"
#include "vyuhaone/square.hpp"

namespace vyuhaone
{
    class Position
    {
    public:
    Position() = default;    
    static Position StartingPosition();

    Bitboard pieces(Colour colour, PieceType piece_type) const;
    Bitboard occupancy(Colour colour) const;
    Bitboard occupancy() const;

    Colour side_to_move() const;
    CastlingRights castling_rights() const;
    Square en_passant_square() const;

    std::uint16_t halfmove_clock() const;
    std::uint16_t fullmove_number() const;

    private:
    static constexpr std::size_t kColourCount = static_cast<std::size_t>(Colour::Count);
    static constexpr std::size_t kPieceTypeCount = static_cast<std::size_t>(PieceType::Count);

    std::array<std::array<Bitboard, kPieceTypeCount>, kColourCount> piece_bitboards_{};
    
    std::array<Bitboard, kColourCount> colour_occupancy_{};
    Bitboard combined_occupancy_{};

    Colour side_to_move_{Colour::White};
    CastlingRights castling_rights_{CastlingRights::None};
    Square en_passant_square_{Square::None};

    std::uint16_t halfmove_clock_{0};
    std::uint16_t fullmove_number_{1};

    void RecomputeOccupancy();
    };
}
