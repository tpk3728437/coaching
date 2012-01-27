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
