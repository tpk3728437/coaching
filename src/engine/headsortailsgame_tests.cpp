#include <limits.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "headsortailsgame.h"
#include "mock_gameplay.h"
#include "mock_player.h"
#include "mock_userevents.h"

using ::testing::_;
using ::testing::Return;
using ::testing::InSequence;
using ::testing::AllOf;
using ::testing::Ge;
using ::testing::Le;
using ::testing::Invoke;


/// Win table
// 00(0), (lose) x
// 00(1), (lose) x 
// 010, (lose) x
// 100, (lose) x
// 110, (win) x
// 011, (win) x
// 101, (win) x
// 111, (super win)

void tailsFlipResult(FlipResult& result)
{
    result.flipResult(Tails);
}

void headsFlipResult(FlipResult& result)
{
    result.flipResult(Heads);
}

void doubleUpTrueResult(DoubleupChoiceResult& result)
{
    result.doubleUp(true);
}

void doubleUpFalseResult(DoubleupChoiceResult& result)
{
    result.doubleUp(false);
}

class HeadsOrTailsGameTest : public ::testing::Test
{
public:
    void NO_DOUBLEUP_USER_EVENT(MockUserEvents& events)
    {
        EXPECT_CALL(events, doesUserWantToDoubleUp(_)).Times(0);
    }

    void EXPECT_DOUBLEUP_CALL_AND_PAYOUT_RESULT(MockUserEvents& events)
    {
        EXPECT_CALL(events, doesUserWantToDoubleUp(_))
            .WillOnce(Invoke(doubleUpFalseResult));
    }

public:
    MockGamePlay play;
    MockPlayer player;
    MockUserEvents events;
};

TEST_F(HeadsOrTailsGameTest, lose_with_two_tails)
{    
    EXPECT_CALL(play, flip(_)).Times(2).WillRepeatedly(Invoke(tailsFlipResult)); 

    EXPECT_CALL(player, onPlayStarted());
    EXPECT_CALL(player, onCoinFlipped(0, Tails));
    EXPECT_CALL(player, onCoinFlipped(1, Tails));
    EXPECT_CALL(player, onBigWin()).Times(0);
    EXPECT_CALL(player, onGameWin()).Times(0);
    EXPECT_CALL(player, onGameLoss());
    EXPECT_CALL(player, onGameEnd());

    NO_DOUBLEUP_USER_EVENT(events);

    HeadsOrTailsGame game(play, player, events);
    game.play();    
}

TEST_F(HeadsOrTailsGameTest, lose_with_heads_then_two_tails)
{
    EXPECT_CALL(play, flip(_)).Times(3)
        .WillOnce(Invoke(headsFlipResult))
        .WillRepeatedly(Invoke(tailsFlipResult));

    InSequence in;
    EXPECT_CALL(player, onPlayStarted());
    EXPECT_CALL(player, onCoinFlipped(0, Heads));
    EXPECT_CALL(player, onCoinFlipped(1, Tails));
    EXPECT_CALL(player, onCoinFlipped(2, Tails));
    EXPECT_CALL(player, onBigWin()).Times(0);
    EXPECT_CALL(player, onGameWin()).Times(0);
    EXPECT_CALL(player, onGameLoss());
    EXPECT_CALL(player, onGameEnd());

    NO_DOUBLEUP_USER_EVENT(events);

    HeadsOrTailsGame game(play, player, events);
    game.play();    
}

TEST_F(HeadsOrTailsGameTest, lose_with_tails_heads_tails_sequence)
{
    EXPECT_CALL(play, flip(_)).Times(3)
        .WillOnce(Invoke(tailsFlipResult))
        .WillOnce(Invoke(headsFlipResult))
        .WillRepeatedly(Invoke(tailsFlipResult));

    InSequence in;
    EXPECT_CALL(player, onPlayStarted());
    EXPECT_CALL(player, onCoinFlipped(0, Tails));
    EXPECT_CALL(player, onCoinFlipped(1, Heads));
    EXPECT_CALL(player, onCoinFlipped(2, Tails));
    EXPECT_CALL(player, onBigWin()).Times(0);
    EXPECT_CALL(player, onGameWin()).Times(0);
    EXPECT_CALL(player, onGameLoss());
    EXPECT_CALL(player, onGameEnd());

    NO_DOUBLEUP_USER_EVENT(events);

    HeadsOrTailsGame game(play, player, events);
    game.play();    
}

TEST_F(HeadsOrTailsGameTest, win_with_heads_heads_tails_sequence)
{
    EXPECT_CALL(play, flip(_)).Times(3)
        .WillOnce(Invoke(headsFlipResult))
        .WillOnce(Invoke(headsFlipResult))
        .WillRepeatedly(Invoke(tailsFlipResult));

    {
    InSequence in; 
    EXPECT_CALL(player, onPlayStarted());
    EXPECT_CALL(player, onCoinFlipped(0, Heads));
    EXPECT_CALL(player, onCoinFlipped(1, Heads));
    EXPECT_CALL(player, onCoinFlipped(2, Tails));
    EXPECT_CALL(player, onBigWin()).Times(0);
    EXPECT_CALL(player, onGameWin());
    EXPECT_CALL(player, onGameLoss()).Times(0);
    EXPECT_CALL(player, onGameEnd()); }

    EXPECT_DOUBLEUP_CALL_AND_PAYOUT_RESULT(events);

    HeadsOrTailsGame game(play, player, events);
    game.play();
}

TEST_F(HeadsOrTailsGameTest, win_with_tails_heads_heads_sequence)
{
    EXPECT_CALL(play, flip(_)).Times(3)
        .WillOnce(Invoke(tailsFlipResult))
        .WillRepeatedly(Invoke(headsFlipResult));

    {
    InSequence in;
    EXPECT_CALL(player, onPlayStarted());
    EXPECT_CALL(player, onCoinFlipped(0, Tails));
    EXPECT_CALL(player, onCoinFlipped(1, Heads));
    EXPECT_CALL(player, onCoinFlipped(2, Heads));
    EXPECT_CALL(player, onBigWin()).Times(0);
    EXPECT_CALL(player, onGameWin());
    EXPECT_CALL(player, onGameLoss()).Times(0);
    EXPECT_CALL(player, onGameEnd()); }
    
    EXPECT_DOUBLEUP_CALL_AND_PAYOUT_RESULT(events);

    HeadsOrTailsGame game(play, player, events);
    game.play();    
}

TEST_F(HeadsOrTailsGameTest, win_with_heads_tails_heads_sequence)
{
    EXPECT_CALL(play, flip(_)).Times(3)
        .WillOnce(Invoke(headsFlipResult))
        .WillOnce(Invoke(tailsFlipResult))
        .WillRepeatedly(Invoke(headsFlipResult));

    { InSequence in;
    EXPECT_CALL(player, onPlayStarted());
    EXPECT_CALL(player, onCoinFlipped(0, Heads));
    EXPECT_CALL(player, onCoinFlipped(1, Tails));
    EXPECT_CALL(player, onCoinFlipped(2, Heads));
    EXPECT_CALL(player, onBigWin()).Times(0);
    EXPECT_CALL(player, onGameWin());
    EXPECT_CALL(player, onGameLoss()).Times(0);
    EXPECT_CALL(player, onGameEnd()); }

    EXPECT_DOUBLEUP_CALL_AND_PAYOUT_RESULT(events);

    HeadsOrTailsGame game(play, player, events);
    game.play();    
}

TEST_F(HeadsOrTailsGameTest, bigwin_with_heads_heads_heads_sequence)
{
    MockGamePlay play;
    EXPECT_CALL(play, flip(_)).Times(3)
        .WillRepeatedly(Invoke(headsFlipResult));

    { InSequence in;
    EXPECT_CALL(player, onPlayStarted());
    EXPECT_CALL(player, onCoinFlipped(AllOf(Ge(0), Le(2)), Heads)).Times(3);
    EXPECT_CALL(player, onGameWin()).Times(0);
    EXPECT_CALL(player, onBigWin());
    EXPECT_CALL(player, onGameLoss()).Times(0);
    EXPECT_CALL(player, onGameEnd()); }

    NO_DOUBLEUP_USER_EVENT(events);

    HeadsOrTailsGame game(play, player, events);
    game.play();    
}

TEST_F(HeadsOrTailsGameTest, doubleup_lose_with_tails)
{
    EXPECT_CALL(play, flip(_)).Times(4)
        .WillOnce(Invoke(tailsFlipResult))
        .WillOnce(Invoke(headsFlipResult))
        .WillOnce(Invoke(headsFlipResult))
        .WillRepeatedly(Invoke(tailsFlipResult));

    EXPECT_CALL(player, onPlayStarted());
    EXPECT_CALL(player, onCoinFlipped(0, Tails));
    EXPECT_CALL(player, onCoinFlipped(1, Heads));
    EXPECT_CALL(player, onCoinFlipped(2, Heads));
    EXPECT_CALL(player, onCoinFlipped(3, Tails));
    EXPECT_CALL(player, onBigWin()).Times(0);
    EXPECT_CALL(player, onGameWin());
    EXPECT_CALL(player, onGameLoss()).Times(1);
    EXPECT_CALL(player, onGameEnd());
    EXPECT_CALL(player, onDoubleUp(false));
    
    EXPECT_CALL(events, doesUserWantToDoubleUp(_))
        .WillOnce(Invoke(doubleUpTrueResult));

    HeadsOrTailsGame game(play, player, events);
    game.play();    
}

TEST_F(HeadsOrTailsGameTest, doubleup_win_with_heads)
{
    EXPECT_CALL(play, flip(_)).Times(4)
        .WillOnce(Invoke(tailsFlipResult))
        .WillOnce(Invoke(headsFlipResult))
        .WillOnce(Invoke(headsFlipResult))
        .WillRepeatedly(Invoke(headsFlipResult));

    EXPECT_CALL(player, onPlayStarted());
    EXPECT_CALL(player, onCoinFlipped(0, Tails));
    EXPECT_CALL(player, onCoinFlipped(1, Heads));
    EXPECT_CALL(player, onCoinFlipped(2, Heads));
    EXPECT_CALL(player, onCoinFlipped(3, Heads));
    EXPECT_CALL(player, onBigWin()).Times(0);
    EXPECT_CALL(player, onGameWin()).Times(2);
    EXPECT_CALL(player, onGameLoss()).Times(0);
    EXPECT_CALL(player, onGameEnd());
    EXPECT_CALL(player, onDoubleUp(true));
    
    EXPECT_CALL(events, doesUserWantToDoubleUp(_))
        .WillOnce(Invoke(doubleUpTrueResult))
        .WillOnce(Invoke(doubleUpFalseResult));

    HeadsOrTailsGame game(play, player, events);
    game.play();    
}

TEST_F(HeadsOrTailsGameTest, doubleup_twice_win_with_heads_then_lose_with_tails)
{
    EXPECT_CALL(play, flip(_)).Times(5)
        .WillOnce(Invoke(tailsFlipResult))
        .WillOnce(Invoke(headsFlipResult))
        .WillOnce(Invoke(headsFlipResult))
        .WillOnce(Invoke(headsFlipResult))
        .WillRepeatedly(Invoke(tailsFlipResult));

    EXPECT_CALL(player, onPlayStarted());
    EXPECT_CALL(player, onCoinFlipped(0, Tails));
    EXPECT_CALL(player, onCoinFlipped(1, Heads));
    EXPECT_CALL(player, onCoinFlipped(2, Heads));
    EXPECT_CALL(player, onCoinFlipped(3, Heads));
    EXPECT_CALL(player, onCoinFlipped(4, Tails));
    EXPECT_CALL(player, onBigWin()).Times(0);
    EXPECT_CALL(player, onGameWin()).Times(2);
    EXPECT_CALL(player, onGameLoss()).Times(1);
    EXPECT_CALL(player, onGameEnd());
    EXPECT_CALL(player, onDoubleUp(true));
    EXPECT_CALL(player, onDoubleUp(false));
    
    EXPECT_CALL(events, doesUserWantToDoubleUp(_))
        .WillRepeatedly(Invoke(doubleUpTrueResult));

    HeadsOrTailsGame game(play, player, events);
    game.play();    
}

TEST_F(HeadsOrTailsGameTest, doubleup_twice_win_with_heads_heads)
{
    EXPECT_CALL(play, flip(_)).Times(5)
        .WillOnce(Invoke(tailsFlipResult))
        .WillRepeatedly(Invoke(headsFlipResult));

    EXPECT_CALL(player, onPlayStarted());
    EXPECT_CALL(player, onCoinFlipped(0, Tails));
    EXPECT_CALL(player, onCoinFlipped(1, Tails));
    EXPECT_CALL(player, onCoinFlipped(2, Heads));
    EXPECT_CALL(player, onCoinFlipped(3, Heads));
    EXPECT_CALL(player, onCoinFlipped(4, Heads));
    EXPECT_CALL(player, onBigWin()).Times(0);
    EXPECT_CALL(player, onGameWin()).Times(3);
    EXPECT_CALL(player, onGameLoss()).Times(0);
    EXPECT_CALL(player, onGameEnd());
    EXPECT_CALL(player, onDoubleUp(true)).Times(2);
    
    EXPECT_CALL(events, doesUserWantToDoubleUp(_))
        .WillOnce(Invoke(doubleUpTrueResult))
        .WillOnce(Invoke(doubleUpTrueResult))
        .WillOnce(Invoke(doubleUpFalseResult));

    HeadsOrTailsGame game(play, player, events);
    game.play();    
}

TEST_F(HeadsOrTailsGameTest, doubleup_twice_win_with_heads_heads_lose_with_tails)
{
    EXPECT_CALL(play, flip(_)).Times(6)
        .WillOnce(Invoke(tailsFlipResult))
        .WillOnce(Invoke(headsFlipResult))
        .WillOnce(Invoke(headsFlipResult))
        .WillOnce(Invoke(headsFlipResult))
        .WillOnce(Invoke(headsFlipResult))
        .WillRepeatedly(Invoke(tailsFlipResult));

    EXPECT_CALL(player, onPlayStarted());
    EXPECT_CALL(player, onCoinFlipped(0, Tails));
    EXPECT_CALL(player, onCoinFlipped(1, Heads));
    EXPECT_CALL(player, onCoinFlipped(2, Heads));
    EXPECT_CALL(player, onCoinFlipped(3, Heads));
    EXPECT_CALL(player, onCoinFlipped(4, Heads));
    EXPECT_CALL(player, onCoinFlipped(5, Tails));
    EXPECT_CALL(player, onBigWin()).Times(0);
    EXPECT_CALL(player, onGameWin()).Times(3);
    EXPECT_CALL(player, onGameLoss()).Times(1);
    EXPECT_CALL(player, onGameEnd());
    EXPECT_CALL(player, onDoubleUp(true)).Times(2);
    EXPECT_CALL(player, onDoubleUp(false));
    
    EXPECT_CALL(events, doesUserWantToDoubleUp(_))
        .WillRepeatedly(Invoke(doubleUpTrueResult));

    HeadsOrTailsGame game(play, player, events);
    game.play();    
}

TEST_F(HeadsOrTailsGameTest, replay)
{    
    EXPECT_CALL(play, flip(_)).Times(4).WillRepeatedly(Invoke(tailsFlipResult)); 

    EXPECT_CALL(player, onPlayStarted()).Times(2);
    EXPECT_CALL(player, onCoinFlipped(0, Tails)).Times(2);
    EXPECT_CALL(player, onCoinFlipped(1, Tails)).Times(2);
    EXPECT_CALL(player, onBigWin()).Times(0);
    EXPECT_CALL(player, onGameWin()).Times(0);
    EXPECT_CALL(player, onGameLoss()).Times(2);
    EXPECT_CALL(player, onGameEnd()).Times(2);

    NO_DOUBLEUP_USER_EVENT(events);

    HeadsOrTailsGame game(play, player, events);
    game.play();
    game.play();
}
