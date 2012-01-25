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
    static_cast<UserCommandObserver*>(&controller)->QuitButtonPressed();
}

TEST_F(ControllerTest, play_button_press_resets_graphics_and_start_new_game)
{
    Controller controller(View());
    EXPECT_CALL(View(), ResetGraphics()).Times(2);
    static_cast<UserCommandObserver*>(&controller)->PlayButtonPressed();

    MockGame mockGame;
    EXPECT_CALL(mockGame, Play());
    controller.setEngine(mockGame);
    static_cast<UserCommandObserver*>(&controller)->PlayButtonPressed();    
}

TEST_F(ControllerTest, doubleup_button_press_resets_doubleup_graphics)
{
    Controller controller(View());
    EXPECT_CALL(View(), ResetDoubleUpScreenGraphics());
    static_cast<UserCommandObserver*>(&controller)->DoubleUpButtonPressed();
}

TEST_F(ControllerTest, payout_button_press_resets_all_graphics)
{
    Controller controller(View());
    EXPECT_CALL(View(), ResetGraphics());
    static_cast<UserCommandObserver*>(&controller)->PayoutButtonPressed();  
}

TEST_F(ControllerTest, coin_flip_results_invalid_index)
{
    Controller controller(View());
    static_cast<Player*>(&controller)->onCoinFlipped(-1, Heads);  
    static_cast<Player*>(&controller)->onCoinFlipped(-2, Heads);  
}

TEST_F(ControllerTest, coin_flip_results_base_game)
{
    Controller controller(View());
    EXPECT_CALL(View(), ShowBaseGameCoin(0, Heads));
    EXPECT_CALL(View(), ShowBaseGameCoin(1, Tails));
    EXPECT_CALL(View(), ShowBaseGameCoin(2, Heads));
    static_cast<Player*>(&controller)->onCoinFlipped(0, Heads);  
    static_cast<Player*>(&controller)->onCoinFlipped(1, Tails);  
    static_cast<Player*>(&controller)->onCoinFlipped(2, Heads);  
}

TEST_F(ControllerTest, coin_flip_results_doubleup_game)
{
    Controller controller(View());
    EXPECT_CALL(View(), ShowDoubleUpCoin(Heads)).Times(2);
    static_cast<Player*>(&controller)->onCoinFlipped(3, Heads);  
    static_cast<Player*>(&controller)->onCoinFlipped(4, Heads);  
}

TEST_F(ControllerTest, on_big_win_event)
{
    Controller controller(View());
    EXPECT_CALL(View(), ShowBigWin());
    static_cast<Player*>(&controller)->onBigWin();  
}

TEST_F(ControllerTest, on_game_win_event)
{
    Controller controller(View());
    EXPECT_CALL(View(), ShowDoubleUpScreen());
    static_cast<Player*>(&controller)->onGameWin();  
}

TEST_F(ControllerTest, on_loss_event)
{
    Controller controller(View());
    EXPECT_CALL(View(), ShowGameLoss());
    static_cast<Player*>(&controller)->onGameLoss();  
}

TEST_F(ControllerTest, on_doubleup_event)
{
    Controller controller(View());
    {
    EXPECT_CALL(View(), ShowDoubleupResult(true));
    static_cast<Player*>(&controller)->onDoubleUp(true);
    }
    {
    EXPECT_CALL(View(), ShowDoubleupResult(false));
    static_cast<Player*>(&controller)->onDoubleUp(false);
    }
}
