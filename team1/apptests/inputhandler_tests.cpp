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

class KeyhandlingTest : public ::testing::Test
{
public:
    KeyhandlingTest() : ::testing::Test(), inputManager(0), inputHandler(0), trigger(0) {
        inputManager = new MockInputManager;
        EXPECT_CALL(*inputManager, setKeyboardEventCallback(An<OIS::KeyListener&>()));
        EXPECT_CALL(*inputManager, setMouseEventCallback(_));
        
        inputHandler = new InputHandler(std::auto_ptr<InputManager>(inputManager), observer);
    }
    ~KeyhandlingTest() {
        delete trigger;
        delete inputHandler;
    }

    void EXPECT_QUIT_BUTTON_PRESS() { 
        EXPECT_CALL(observer, QuitButtonPressed()); 
    }
    
    void TRIGGER_KEY(const OIS::KeyCode keyCode) {
        ASSERT_TRUE(trigger == NULL);
        trigger = new TriggerKey(*inputHandler, keyCode);
        
        EXPECT_CALL(*inputManager, Capture()).WillOnce(Invoke(*trigger));
        Capture();
    }
    
    void Capture() { inputHandler->Capture(); }

private:
    MockUserCommandObserver observer;
    MockInputManager* inputManager; // ref: ownership passed to inputHandler
    InputHandler* inputHandler;
    TriggerKey* trigger;
};

TEST_F(KeyhandlingTest, quit_button_pressed)
{
    EXPECT_QUIT_BUTTON_PRESS();
    
    TRIGGER_KEY(OIS::KC_ESCAPE);
}
