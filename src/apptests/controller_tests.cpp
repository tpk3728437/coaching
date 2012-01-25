#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "controller.h"
#include "viewinterface.h"
#include "headsortailsgame.h"
#include "inputhandler.h"
#include "mock_game.h"
#include "mock_view.h"

using ::testing::_;
using ::testing::Return;


class ButtonDriver
{
public:
    ButtonDriver(UserCommandObserver& userCommandObserver) : mUserCommandObserver(userCommandObserver) {}
    void PressQuitButton() { mUserCommandObserver.QuitButtonPressed(); }
    void PressPlayButton() { mUserCommandObserver.PlayButtonPressed(); }
    void PressDoubleUpButton() { mUserCommandObserver.DoubleUpButtonPressed(); }
    void PressPayoutButton() { mUserCommandObserver.PayoutButtonPressed(); }

private:
    UserCommandObserver& mUserCommandObserver;
};

class GameDriver
{
public:
    GameDriver(Player& player) : mPlayer(player){}
    void FlipCoin(int index, Side side) { mPlayer.onCoinFlipped(index, side); }
    void TriggerBigWinEvent() { mPlayer.onBigWin(); }
    void TriggerGameWinEvent() { mPlayer.onGameWin(); }
    void TriggerGameLossEvent() { mPlayer.onGameLoss(); }  
    void TriggerDoubleUpWinEvent() { mPlayer.onDoubleUp(true); }
    void TriggerDoubleUpLoseEvent() { mPlayer.onDoubleUp(false); }
          
private:
    Player& mPlayer; 
};


class ControllerTest : public ::testing::Test
{
public:
    ControllerTest() {}
    ~ControllerTest() {}
    MockView& View() { return mockView; }
private:
    MockView mockView;
    ViewportSize size;
};

TEST_F(ControllerTest, initialization)
{        
    Controller controller(View());
}

TEST_F(ControllerTest, quit_button_press_quits_view_rendering)
{
    Controller controller(View());
    EXPECT_CALL(View(), Quit());
    ButtonDriver driver(controller);
    driver.PressQuitButton();
}

TEST_F(ControllerTest, play_button_press_resets_graphics_and_start_new_game)
{
    Controller controller(View());
    EXPECT_CALL(View(), ResetGraphics()).Times(2);
    ButtonDriver driver(controller);
    driver.PressPlayButton();

    MockGame mockGame;
    EXPECT_CALL(mockGame, Play());
    controller.setEngine(mockGame);
    driver.PressPlayButton();
}

TEST_F(ControllerTest, doubleup_button_press_resets_doubleup_graphics)
{
    Controller controller(View());
    EXPECT_CALL(View(), ResetDoubleUpScreenGraphics());
    ButtonDriver driver(controller);
    driver.PressDoubleUpButton();
}

TEST_F(ControllerTest, payout_button_press_resets_all_graphics)
{
    Controller controller(View());
    EXPECT_CALL(View(), ResetGraphics());
    ButtonDriver driver(controller);
    driver.PressPayoutButton();
}

TEST_F(ControllerTest, coin_flip_results_invalid_index)
{
    Controller controller(View());
    GameDriver driver(controller);
    driver.FlipCoin(-1, Heads);
    driver.FlipCoin(-2, Heads);
}

TEST_F(ControllerTest, coin_flip_results_base_game)
{
    Controller controller(View());
    EXPECT_CALL(View(), ShowBaseGameCoin(0, Heads));
    EXPECT_CALL(View(), ShowBaseGameCoin(1, Tails));
    EXPECT_CALL(View(), ShowBaseGameCoin(2, Heads));

    GameDriver driver(controller);
    driver.FlipCoin(0, Heads);
    driver.FlipCoin(1, Tails);
    driver.FlipCoin(2, Heads);
}

TEST_F(ControllerTest, coin_flip_results_doubleup_game)
{
    Controller controller(View());
    EXPECT_CALL(View(), ShowDoubleUpCoin(Heads)).Times(2);
    GameDriver driver(controller);
    driver.FlipCoin(3, Heads);
    driver.FlipCoin(4, Heads);
}

TEST_F(ControllerTest, on_big_win_event)
{
    Controller controller(View());
    EXPECT_CALL(View(), ShowBigWin());

    GameDriver driver(controller);
    driver.TriggerBigWinEvent();
}

TEST_F(ControllerTest, on_game_win_event)
{
    Controller controller(View());
    EXPECT_CALL(View(), ShowDoubleUpScreen());

    GameDriver driver(controller);
    driver.TriggerGameWinEvent();
}

TEST_F(ControllerTest, on_loss_event)
{
    Controller controller(View());
    EXPECT_CALL(View(), ShowGameLoss());

    GameDriver driver(controller);
    driver.TriggerGameLossEvent();
}

TEST_F(ControllerTest, on_doubleup_lose_event)
{
    Controller controller(View());
    EXPECT_CALL(View(), ShowDoubleupResult(false));
    
    GameDriver driver(controller);
    driver.TriggerDoubleUpLoseEvent();
}

TEST_F(ControllerTest, on_doubleup_win_event)
{
    Controller controller(View());
    EXPECT_CALL(View(), ShowDoubleupResult(true));
    
    GameDriver driver(controller);
    driver.TriggerDoubleUpWinEvent();    
}
