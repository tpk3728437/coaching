#include <limits.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "HeadsOrTailsGame.h"
#include "mock_gameplay.h"
#include "mock_player.h"

using ::testing::_;
using ::testing::Return;
using ::testing::InSequence;
using ::testing::AllOf;
using ::testing::Ge;
using ::testing::Le;

class MockUserEvents : public UserEvents
{
public:
    MOCK_METHOD0(DoubleUp, bool());
};


/// Win table
// 00(0), (lose) x
// 00(1), (lose) x 
// 010, (lose) x
// 100, (lose) x
// 110, (win) x
// 011, (win) x
// 101, (win) x
// 111, (super win)

TEST(FlipCoin, lose_with_two_tails)
{
    MockGamePlay play;
    EXPECT_CALL(play, Flip()).Times(2).WillRepeatedly(Return(Tails));

    MockPlayer player;
    EXPECT_CALL(player, onPlayStarted());
    EXPECT_CALL(player, onCoinFlipped(0, Tails));
    EXPECT_CALL(player, onCoinFlipped(1, Tails));
    EXPECT_CALL(player, onBigWin()).Times(0);
    EXPECT_CALL(player, onGameWin()).Times(0);
    EXPECT_CALL(player, onGameLoss());
    EXPECT_CALL(player, onGameEnd());

    MockUserEvents events;
    EXPECT_CALL(events, DoubleUp()).Times(0);

    HeadsOrTailsGame game(play, player, events);
    game.Play();    
}

TEST(FlipCoin, lose_with_heads_then_two_tails)
{
    MockGamePlay play;
    EXPECT_CALL(play, Flip()).Times(3)
        .WillOnce(Return(Heads))
        .WillRepeatedly(Return(Tails));

    InSequence in;
    MockPlayer player;
    EXPECT_CALL(player, onPlayStarted());
    EXPECT_CALL(player, onCoinFlipped(0, Heads));
    EXPECT_CALL(player, onCoinFlipped(1, Tails));
    EXPECT_CALL(player, onCoinFlipped(2, Tails));
    EXPECT_CALL(player, onBigWin()).Times(0);
    EXPECT_CALL(player, onGameWin()).Times(0);
    EXPECT_CALL(player, onGameLoss());
    EXPECT_CALL(player, onGameEnd());

    MockUserEvents events;
    EXPECT_CALL(events, DoubleUp()).Times(0);

    HeadsOrTailsGame game(play, player, events);
    game.Play();    
}

TEST(FlipCoin, lose_with_tails_heads_tails_sequence)
{
    MockGamePlay play;
    EXPECT_CALL(play, Flip()).Times(3)
        .WillOnce(Return(Tails))
        .WillOnce(Return(Heads))
        .WillRepeatedly(Return(Tails));

    InSequence in;
    MockPlayer player;
    EXPECT_CALL(player, onPlayStarted());
    EXPECT_CALL(player, onCoinFlipped(0, Tails));
    EXPECT_CALL(player, onCoinFlipped(1, Heads));
    EXPECT_CALL(player, onCoinFlipped(2, Tails));
    EXPECT_CALL(player, onBigWin()).Times(0);
    EXPECT_CALL(player, onGameWin()).Times(0);
    EXPECT_CALL(player, onGameLoss());
    EXPECT_CALL(player, onGameEnd());

    MockUserEvents events;
    EXPECT_CALL(events, DoubleUp()).Times(0);

    HeadsOrTailsGame game(play, player, events);
    game.Play();    
}

TEST(FlipCoin, win_with_heads_heads_tails_sequence)
{
    MockGamePlay play;
    EXPECT_CALL(play, Flip()).Times(3)
        .WillOnce(Return(Heads))
        .WillOnce(Return(Heads))
        .WillRepeatedly(Return(Tails));

    MockPlayer player; {
    InSequence in; 
    EXPECT_CALL(player, onPlayStarted());
    EXPECT_CALL(player, onCoinFlipped(0, Heads));
    EXPECT_CALL(player, onCoinFlipped(1, Heads));
    EXPECT_CALL(player, onCoinFlipped(2, Tails));
    EXPECT_CALL(player, onBigWin()).Times(0);
    EXPECT_CALL(player, onGameWin());
    EXPECT_CALL(player, onGameLoss()).Times(0);
    EXPECT_CALL(player, onGameEnd()); }

    MockUserEvents events;
    EXPECT_CALL(events, DoubleUp())
        .WillOnce(Return(false));

    HeadsOrTailsGame game(play, player, events);
    game.Play();    
}

TEST(FlipCoin, win_with_tails_heads_heads_sequence)
{
    MockGamePlay play;
    EXPECT_CALL(play, Flip()).Times(3)
        .WillOnce(Return(Tails))
        .WillRepeatedly(Return(Heads));

    MockPlayer player; {
    InSequence in;
    EXPECT_CALL(player, onPlayStarted());
    EXPECT_CALL(player, onCoinFlipped(0, Tails));
    EXPECT_CALL(player, onCoinFlipped(1, Heads));
    EXPECT_CALL(player, onCoinFlipped(2, Heads));
    EXPECT_CALL(player, onBigWin()).Times(0);
    EXPECT_CALL(player, onGameWin());
    EXPECT_CALL(player, onGameLoss()).Times(0);
    EXPECT_CALL(player, onGameEnd()); }
    
    MockUserEvents events;
    EXPECT_CALL(events, DoubleUp())
        .WillOnce(Return(false));

    HeadsOrTailsGame game(play, player, events);
    game.Play();    
}

TEST(FlipCoin, win_with_heads_tails_heads_sequence)
{
    MockGamePlay play;
    EXPECT_CALL(play, Flip()).Times(3)
        .WillOnce(Return(Heads))
        .WillOnce(Return(Tails))
        .WillRepeatedly(Return(Heads));

    MockPlayer player; {
    InSequence in;
    EXPECT_CALL(player, onPlayStarted());
    EXPECT_CALL(player, onCoinFlipped(0, Heads));
    EXPECT_CALL(player, onCoinFlipped(1, Tails));
    EXPECT_CALL(player, onCoinFlipped(2, Heads));
    EXPECT_CALL(player, onBigWin()).Times(0);
    EXPECT_CALL(player, onGameWin());
    EXPECT_CALL(player, onGameLoss()).Times(0);
    EXPECT_CALL(player, onGameEnd()); }

    MockUserEvents events;
    EXPECT_CALL(events, DoubleUp())
        .WillOnce(Return(false));

    HeadsOrTailsGame game(play, player, events);
    game.Play();    
}

TEST(FlipCoin, win_with_heads_heads_heads_sequence)
{
    MockGamePlay play;
    EXPECT_CALL(play, Flip()).Times(3)
        .WillRepeatedly(Return(Heads));

    MockPlayer player; {
    InSequence in;
    EXPECT_CALL(player, onPlayStarted());
    EXPECT_CALL(player, onCoinFlipped(AllOf(Ge(0), Le(2)), Heads)).Times(3);
    EXPECT_CALL(player, onBigWin());
    EXPECT_CALL(player, onGameWin());
    EXPECT_CALL(player, onGameLoss()).Times(0);
    EXPECT_CALL(player, onGameEnd()); }

    MockUserEvents events;
    EXPECT_CALL(events, DoubleUp()).Times(0);

    HeadsOrTailsGame game(play, player, events);
    game.Play();    
}
