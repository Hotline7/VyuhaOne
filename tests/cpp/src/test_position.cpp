#include "vyuhaone/position.hpp"
#include "vyuhaone/square.hpp"
#include "vyuhaone/types.hpp"

#include <gtest/gtest.h>

TEST(PositionTest, StartingSideIsWhite)
{
    const auto position = vyuhaone::Position::StartingPosition();

    EXPECT_EQ(position.side_to_move(), vyuhaone::Colour::White);
}

TEST(PositionTest, StartingPositionHasCorrectOccupancies)
{
    const auto position = vyuhaone::Position::StartingPosition();

    EXPECT_EQ(
        position.occupancy(vyuhaone::Colour::White),
        vyuhaone::Bitboard{0x000000000000FFFFULL});

    EXPECT_EQ(
        position.occupancy(vyuhaone::Colour::Black),
        vyuhaone::Bitboard{0xFFFF000000000000ULL});

    EXPECT_EQ(
        position.occupancy(),
        vyuhaone::Bitboard{0xFFFF00000000FFFFULL});
}

TEST(PositionTest, DefaultConstructorIsEmpty)
{
    const vyuhaone::Position position{};

    EXPECT_EQ(
        position.occupancy(vyuhaone::Colour::White),
        vyuhaone::Bitboard{0});

    EXPECT_EQ(
        position.occupancy(vyuhaone::Colour::Black),
        vyuhaone::Bitboard{0});

    EXPECT_EQ(
        position.occupancy(),
        vyuhaone::Bitboard{0});

    EXPECT_EQ(
        position.castling_rights(),
        vyuhaone::CastlingRights::None);
}

TEST(PositionTest, StartingRuleStateIsCorrect)
{
    const auto position = vyuhaone::Position::StartingPosition();

    EXPECT_EQ(
        position.castling_rights(),
        vyuhaone::CastlingRights::All);

    EXPECT_EQ(
        position.en_passant_square(),
        vyuhaone::Square::None);

    EXPECT_EQ(position.halfmove_clock(), 0);
    EXPECT_EQ(position.fullmove_number(), 1);
}

TEST(PositionTest, StartingPositionHasCorrectPieceBitboards)
{
    const auto position = vyuhaone::Position::StartingPosition();

    // White pieces.
    EXPECT_EQ(
        position.pieces(
            vyuhaone::Colour::White,
            vyuhaone::PieceType::Pawn),
        vyuhaone::Bitboard{0x000000000000FF00ULL});

    EXPECT_EQ(
        position.pieces(
            vyuhaone::Colour::White,
            vyuhaone::PieceType::Knight),
        vyuhaone::Bitboard{0x0000000000000042ULL});

    EXPECT_EQ(
        position.pieces(
            vyuhaone::Colour::White,
            vyuhaone::PieceType::Bishop),
        vyuhaone::Bitboard{0x0000000000000024ULL});

    EXPECT_EQ(
        position.pieces(
            vyuhaone::Colour::White,
            vyuhaone::PieceType::Rook),
        vyuhaone::Bitboard{0x0000000000000081ULL});

    EXPECT_EQ(
        position.pieces(
            vyuhaone::Colour::White,
            vyuhaone::PieceType::Queen),
        vyuhaone::Bitboard{0x0000000000000008ULL});

    EXPECT_EQ(
        position.pieces(
            vyuhaone::Colour::White,
            vyuhaone::PieceType::King),
        vyuhaone::Bitboard{0x0000000000000010ULL});

    // Black pieces.
    EXPECT_EQ(
        position.pieces(
            vyuhaone::Colour::Black,
            vyuhaone::PieceType::Pawn),
        vyuhaone::Bitboard{0x00FF000000000000ULL});

    EXPECT_EQ(
        position.pieces(
            vyuhaone::Colour::Black,
            vyuhaone::PieceType::Knight),
        vyuhaone::Bitboard{0x4200000000000000ULL});

    EXPECT_EQ(
        position.pieces(
            vyuhaone::Colour::Black,
            vyuhaone::PieceType::Bishop),
        vyuhaone::Bitboard{0x2400000000000000ULL});

    EXPECT_EQ(
        position.pieces(
            vyuhaone::Colour::Black,
            vyuhaone::PieceType::Rook),
        vyuhaone::Bitboard{0x8100000000000000ULL});

    EXPECT_EQ(
        position.pieces(
            vyuhaone::Colour::Black,
            vyuhaone::PieceType::Queen),
        vyuhaone::Bitboard{0x0800000000000000ULL});

    EXPECT_EQ(
        position.pieces(
            vyuhaone::Colour::Black,
            vyuhaone::PieceType::King),
        vyuhaone::Bitboard{0x1000000000000000ULL});
}

TEST(PositionTest, OccupanciesDoNotOverlap)
{
    const auto position = vyuhaone::Position::StartingPosition();

    const auto white_occupancy =
        position.occupancy(vyuhaone::Colour::White);

    const auto black_occupancy =
        position.occupancy(vyuhaone::Colour::Black);

    EXPECT_EQ(
        white_occupancy & black_occupancy,
        vyuhaone::Bitboard{0});
}