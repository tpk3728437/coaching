#include <limits.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "HeadsOrTailsGame.h"

using ::testing::_;
using ::testing::Return;

class MockGamePlay : public GamePlay
{
public:
//    int Flip() const { return 1; }
    MOCK_CONST_METHOD0(Flip, int());
};

TEST(CalculatorTest, PlayOneRound_resultTails) 
{
    MockGamePlay play;
    ON_CALL(play, Flip()).WillByDefault(Return(0));

    HeadsOrTailsGame game(play);
    EXPECT_EQ(game.Play(), HeadsOrTailsGame::Tails);
}
