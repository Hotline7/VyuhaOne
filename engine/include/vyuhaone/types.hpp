#pragma once
#include <cstdint>

namespace vyuhaone
{
    using Bitboard = std::uint64_t;

    enum class Colour : std::uint8_t
    {
         White = 0, 
         Black,
         Count
    };
    
    enum class PieceType : std::uint8_t
    { 
        Pawn = 0, 
        Knight,
        Bishop,
        Rook,
        Queen,
        King,
        
        Count//,
        //None = 255
    };

    
}