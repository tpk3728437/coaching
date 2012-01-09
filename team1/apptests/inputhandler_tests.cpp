#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "inputhandler.h"

class MockUserCommandObserver : public UserCommandObserver
{
public:
    MOCK_METHOD0(QuitButtonPressed, void());
    MOCK_METHOD0(PlayButtonPressed, void());
    MOCK_METHOD0(DoubleUpButtonPressed, void());
    MOCK_METHOD0(PayoutButtonPressed, void());
};

TEST(KeyhandlingTests, quit_button_pressed)
{
    MockUserCommandObserver observer;
    EXPECT_CALL(observer, QuitButtonPressed());
    OIS::ParamList params;
    
    InputHandler inputHandler(params, 100, 100, observer);
}
