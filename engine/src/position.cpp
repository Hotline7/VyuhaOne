#include "vyuhaone/position.hpp"

namespace vyuhaone
{
    Colour Position::side_to_move() const
    {
        return side_to_move_;
    }

    CastlingRights Position::castling_rights() const
    {
        return castling_rights_;
    }

    Square Position::en_passant_square() const
    {
        return en_passant_square_;
    }

    std::uint16_t Position::halfmove_clock() const
    {
        return halfmove_clock_;
    }

    std::uint16_t Position::fullmove_number() const
    {
        return fullmove_number_;
    }

    Bitboard Position::pieces(Colour colour, PieceType piece_type) const
    {
        return piece_bitboards_[static_cast<std::size_t>(colour)]
        [static_cast<std::size_t>(piece_type)];
    }
    Bitboard Position::occupancy(Colour colour) const
    {
        return colour_occupancy_[static_cast<std::size_t>(colour)];
    }
    Bitboard Position::occupancy() const
    {
        return combined_occupancy_;
    }

    void Position::RecomputeOccupancy()
    {
        combined_occupancy_ = 0;
        for (std::size_t colour_index = 0; colour_index < kColourCount; ++colour_index)
        {
            Bitboard colour_occ = 0;
            for (std::size_t piece_type_index = 0; piece_type_index < kPieceTypeCount; ++piece_type_index)
            {
                colour_occ |= piece_bitboards_[colour_index][piece_type_index];
            }
            colour_occupancy_[colour_index] = colour_occ;
            combined_occupancy_ |= colour_occ;
        }
    }

    Position Position::StartingPosition()
    {
        Position position;

        // White piece_bitboards
        position.piece_bitboards_[static_cast<std::size_t>(Colour::White)][static_cast<std::size_t>(PieceType::Pawn)] = Bitboard(0x000000000000FF00);
        position.piece_bitboards_[static_cast<std::size_t>(Colour::White)][static_cast<std::size_t>(PieceType::Knight)] = Bitboard(0x0000000000000042);
        position.piece_bitboards_[static_cast<std::size_t>(Colour::White)][static_cast<std::size_t>(PieceType::Bishop)] = Bitboard(0x0000000000000024);
        position.piece_bitboards_[static_cast<std::size_t>(Colour::White)][static_cast<std::size_t>(PieceType::Rook)] = Bitboard(0x0000000000000081);
        position.piece_bitboards_[static_cast<std::size_t>(Colour::White)][static_cast<std::size_t>(PieceType::Queen)] = Bitboard(0x00000000000008);
        position.piece_bitboards_[static_cast<std::size_t>(Colour::White)][static_cast<std::size_t>(PieceType::King)] = Bitboard(0x00000000000010);

        // Black piece_bitboards
        position.piece_bitboards_[static_cast<std::size_t>(Colour::Black)][static_cast<std::size_t>(PieceType::Pawn)] = Bitboard(0x00FF000000000000);
        position.piece_bitboards_[static_cast<std::size_t>(Colour::Black)][static_cast<std::size_t>(PieceType::Knight)] = Bitboard(0x4200000000000000);
        position.piece_bitboards_[static_cast<std::size_t>(Colour::Black)][static_cast<std::size_t>(PieceType::Bishop)] = Bitboard(0x2400000000000000);
        position.piece_bitboards_[static_cast<std::size_t>(Colour::Black)][static_cast<std::size_t>(PieceType::Rook)] = Bitboard(0x8100000000000000);
        position.piece_bitboards_[static_cast<std::size_t>(Colour::Black)][static_cast<std::size_t>(PieceType::Queen)] = Bitboard(0x0800000000000000);
        position.piece_bitboards_[static_cast<std::size_t>(Colour::Black)][static_cast<std::size_t>(PieceType::King)] = Bitboard(0x1000000000000000);

        // Set other position attributes
        position.side_to_move_ = Colour::White;
        position.castling_rights_ = CastlingRights::All;
        position.en_passant_square_ = Square::None;
        position.halfmove_clock_ = 0;
        position.fullmove_number_ = 1;

        position.RecomputeOccupancy();
        return position;
    }
}