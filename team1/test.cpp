#include <limits.h>
#include "gtest/gtest.h"
#include "HeadsOrTailsGame.h"


TEST(CalculatorTest, PlayOneRound) 
{
    HeadsOrTailsGame game;
    EXPECT_EQ(game.Play(), HeadsOrTailsGame::Tails);
}
