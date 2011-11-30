#include <limits.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "HeadsOrTailsGame.h"

using ::testing::_;
using ::testing::Return;

class MockGamePlay : public GamePlay
{
public:
    MOCK_CONST_METHOD0(Flip, int());
};

TEST(CoinFlipTest, PlayOneRound_resultTails) 
{
    MockGamePlay play;
    EXPECT_CALL(play, Flip()).Times(1).WillOnce(Return(0));

    HeadsOrTailsGame game(play);
    EXPECT_EQ(game.Play(), HeadsOrTailsGame::Tails);
}

TEST(CoinFlipTest, PlayOneRound_resultHeads)
{
    MockGamePlay play;
    EXPECT_CALL(play, Flip()).Times(1).WillOnce(Return(1));


    HeadsOrTailsGame game(play);
    EXPECT_EQ(game.Play(), HeadsOrTailsGame::Heads);
}
