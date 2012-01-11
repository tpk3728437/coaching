#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "inputhandler.h"
#include <memory>

using ::testing::_;
using ::testing::SaveArg;
using ::testing::Invoke;
using ::testing::An;

class MockUserCommandObserver : public UserCommandObserver
{
public:
    MOCK_METHOD0(QuitButtonPressed, void());
    MOCK_METHOD0(PlayButtonPressed, void());
    MOCK_METHOD0(DoubleUpButtonPressed, void());
    MOCK_METHOD0(PayoutButtonPressed, void());
};

class MockInputManager : public InputManager
{
public:
    MOCK_METHOD1(setKeyboardEventCallback, void(OIS::KeyListener& listener));
    MOCK_METHOD1(setMouseEventCallback, void(OIS::MouseListener& listener));
    MOCK_METHOD0(Capture, void());
};

class TriggerKey
{
public:
    TriggerKey(OIS::KeyListener& keyEventListener, const OIS::KeyCode keyCode) : mKeyEventListener(keyEventListener), mKeyCode(keyCode) {}
    void operator()() {
        OIS::KeyEvent event(NULL, mKeyCode, 25);
        EXPECT_TRUE(mKeyEventListener.keyPressed(event));
    }
private:
    OIS::KeyListener& mKeyEventListener;
    const OIS::KeyCode mKeyCode;
};

TEST(KeyhandlingTests, quit_button_pressed)
{
    MockUserCommandObserver observer;
    EXPECT_CALL(observer, QuitButtonPressed());
    
    MockInputManager* inputManager = new MockInputManager;
    EXPECT_CALL(*inputManager, setKeyboardEventCallback(An<OIS::KeyListener&>()));
    EXPECT_CALL(*inputManager, setMouseEventCallback(_));
    
    InputHandler inputHandler(std::auto_ptr<InputManager>(inputManager), observer);
    TriggerKey trigger(inputHandler, OIS::KC_ESCAPE);
    EXPECT_CALL(*inputManager, Capture()).WillOnce(Invoke(trigger));

    inputHandler.Capture();
}
