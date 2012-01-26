#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "inputhandler.h"
#include "mock_usercommandobserver.h"
#include "mock_inputmanager.h"
#include <memory>

using ::testing::_;
using ::testing::SaveArg;
using ::testing::Invoke;
using ::testing::An;

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
        EXPECT_CALL(observer, quitButtonPressed()); 
    }
    
    void EXPECT_PLAY_BUTTON_PRESS() { 
        EXPECT_CALL(observer, playButtonPressed());
    }
    
    void EXPECT_DOUBLEUP_BUTTON_PRESS() { 
        EXPECT_CALL(observer, doubleUpButtonPressed());
    }

    void EXPECT_PAYOUT_BUTTON_PRESS() { 
        EXPECT_CALL(observer, payoutButtonPressed());
    }
    
    void TRIGGER_KEY(const OIS::KeyCode keyCode) {
        ASSERT_TRUE(trigger == NULL);
        trigger = new TriggerKey(*inputHandler, keyCode);
        
        EXPECT_CALL(*inputManager, capture()).WillOnce(Invoke(*trigger));
        Capture();
    }
    
    void Capture() { inputHandler->capture(); }

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

TEST_F(KeyhandlingTest, play_button_pressed)
{
    EXPECT_PLAY_BUTTON_PRESS();
    
    TRIGGER_KEY(OIS::KC_P);
}

TEST_F(KeyhandlingTest, doubleup_button_pressed)
{
    EXPECT_DOUBLEUP_BUTTON_PRESS();
    
    TRIGGER_KEY(OIS::KC_Y);
}

TEST_F(KeyhandlingTest, payout_button_pressed)
{
    EXPECT_PAYOUT_BUTTON_PRESS();
    
    TRIGGER_KEY(OIS::KC_N);
}
