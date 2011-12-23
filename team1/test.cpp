#include <limits.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "HeadsOrTailsGame.h"
#include "mock_gameplay.h"
#include "mock_player.h"

using ::testing::_;
using ::testing::Return;
using ::testing::Eq;


TEST(FlipCoin, lose_with_two_tails)
{
    MockGamePlay play;
    EXPECT_CALL(play, Flip()).Times(2).WillRepeatedly(Return(Tails));

    MockPlayer player;
    EXPECT_CALL(player, onPlayStarted());
    EXPECT_CALL(player, onCoinFlipped(Eq(0), Tails));
    EXPECT_CALL(player, onCoinFlipped(Eq(1), Tails));
    EXPECT_CALL(player, onGameWin()).Times(0);
    EXPECT_CALL(player, onGameLoss());
    EXPECT_CALL(player, onGameEnd());

    HeadsOrTailsGame game(play, player);
    game.Play();    
}

TEST(FlipCoin, lose_with_heads_then_two_tails)
{
    MockGamePlay play;
    EXPECT_CALL(play, Flip()).Times(3)
        .WillOnce(Return(Heads))
        .WillRepeatedly(Return(Tails));

    MockPlayer player;
    EXPECT_CALL(player, onPlayStarted());
    EXPECT_CALL(player, onCoinFlipped(Eq(0), Heads));
    EXPECT_CALL(player, onCoinFlipped(Eq(1), Tails));
    EXPECT_CALL(player, onCoinFlipped(Eq(2), Tails));
    EXPECT_CALL(player, onGameWin()).Times(0);
    EXPECT_CALL(player, onGameLoss());
    EXPECT_CALL(player, onGameEnd());

    HeadsOrTailsGame game(play, player);
    game.Play();    
}

