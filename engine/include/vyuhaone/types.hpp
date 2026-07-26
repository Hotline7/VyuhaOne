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

    enum class CastlingRights : std::uint8_t
    {
        None = 0,
        kWhiteKingside = 0b0001,  // Bit 0: 0001
        kWhiteQueenside = 0b0010, // Bit 1: 0010
        kBlackKingside = 0b0100,  // Bit 2: 0100
        kBlackQueenside = 0b1000, // Bit 3: 1000
        
        WhiteMask = 0b0011, // kWhiteKingside | kWhiteQueenside
        BlackMask = 0b1100, // kBlackKingside | kBlackQueenside
        
        All = 0b1111 // WhiteMask | BlackMask
    };
}