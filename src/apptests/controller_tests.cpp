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
    void pressQuitButton() { mUserCommandObserver.quitButtonPressed(); }
    void pressPlayButton() { mUserCommandObserver.playButtonPressed(); }
    void pressDoubleUpButton() { mUserCommandObserver.doubleUpButtonPressed(); }
    void pressPayoutButton() { mUserCommandObserver.payoutButtonPressed(); }

private:
    UserCommandObserver& mUserCommandObserver;
};

class GameDriver
{
public:
    GameDriver(Player& player) : mPlayer(player){}
    void flipCoin(int index, Side side) { mPlayer.onCoinFlipped(index, side); }
    void triggerBigWinEvent() { mPlayer.onBigWin(); }
    void triggerGameWinEvent() { mPlayer.onGameWin(); }
    void triggerGameLossEvent() { mPlayer.onGameLoss(); }
    void triggerDoubleUpWinEvent() { mPlayer.onDoubleUp(true); }
    void triggerDoubleUpLoseEvent() { mPlayer.onDoubleUp(false); }
          
private:
    Player& mPlayer; 
};


class ControllerTest : public ::testing::Test
{
public:
    ControllerTest() {}
    ~ControllerTest() {}
    MockView& view() { return mockView; }
private:
    MockView mockView;
    ViewportSize size;
};

TEST_F(ControllerTest, initialization)
{        
    Controller controller(view());
}

TEST_F(ControllerTest, quit_button_press_quits_view_rendering)
{
    Controller controller(view());
    EXPECT_CALL(view(), quit());
    ButtonDriver driver(controller);
    driver.pressQuitButton();
}

TEST_F(ControllerTest, play_button_press_resets_graphics_and_start_new_game)
{
    Controller controller(view());
    EXPECT_CALL(view(), resetGraphics()).Times(2);
    ButtonDriver driver(controller);
    driver.pressPlayButton();

    MockGame mockGame;
    EXPECT_CALL(mockGame, play());
    controller.setEngine(mockGame);
    driver.pressPlayButton();
}

TEST_F(ControllerTest, doubleup_button_press_resets_doubleup_graphics)
{
    Controller controller(view());
    EXPECT_CALL(view(), resetDoubleUpScreenGraphics());
    ButtonDriver driver(controller);
    driver.pressDoubleUpButton();
}

TEST_F(ControllerTest, payout_button_press_resets_all_graphics)
{
    Controller controller(view());
    EXPECT_CALL(view(), resetGraphics());
    ButtonDriver driver(controller);
    driver.pressPayoutButton();
}

TEST_F(ControllerTest, coin_flip_results_invalid_index)
{
    Controller controller(view());
    GameDriver driver(controller);
    driver.flipCoin(-1, Heads);
    driver.flipCoin(-2, Heads);
}

TEST_F(ControllerTest, coin_flip_results_base_game)
{
    Controller controller(view());
    EXPECT_CALL(view(), showBaseGameCoin(0, Heads));
    EXPECT_CALL(view(), showBaseGameCoin(1, Tails));
    EXPECT_CALL(view(), showBaseGameCoin(2, Heads));

    GameDriver driver(controller);
    driver.flipCoin(0, Heads);
    driver.flipCoin(1, Tails);
    driver.flipCoin(2, Heads);
}

TEST_F(ControllerTest, coin_flip_results_doubleup_game)
{
    Controller controller(view());
    EXPECT_CALL(view(), showDoubleUpCoin(Heads)).Times(2);
    GameDriver driver(controller);
    driver.flipCoin(3, Heads);
    driver.flipCoin(4, Heads);
}

TEST_F(ControllerTest, on_big_win_event)
{
    Controller controller(view());
    EXPECT_CALL(view(), showBigWin());

    GameDriver driver(controller);
    driver.triggerBigWinEvent();
}

TEST_F(ControllerTest, on_game_win_event)
{
    Controller controller(view());
    EXPECT_CALL(view(), showDoubleUpScreen());

    GameDriver driver(controller);
    driver.triggerGameWinEvent();
}

TEST_F(ControllerTest, on_loss_event)
{
    Controller controller(view());
    EXPECT_CALL(view(), showGameLoss());

    GameDriver driver(controller);
    driver.triggerGameLossEvent();
}

TEST_F(ControllerTest, on_doubleup_lose_event)
{
    Controller controller(view());
    EXPECT_CALL(view(), showDoubleupResult(false));
    
    GameDriver driver(controller);
    driver.triggerDoubleUpLoseEvent();
}

TEST_F(ControllerTest, on_doubleup_win_event)
{
    Controller controller(view());
    EXPECT_CALL(view(), showDoubleupResult(true));
    
    GameDriver driver(controller);
    driver.triggerDoubleUpWinEvent();
}
