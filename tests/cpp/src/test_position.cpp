#include "vyuhaone/position.hpp"

#include <gtest/gtest.h>

TEST(PositionTest, StartingSideIsWhite)
{
    const auto position = vyuhaone::Position::StartingPosition();

    EXPECT_EQ(position.side_to_move(), vyuhaone::Colour::White);
}