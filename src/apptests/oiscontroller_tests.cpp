#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "oiscontroller.h"
#include "viewinterface.h"
#include "inputmanager.h"
#include "mock_game.h"
#include "mock_view.h"

using ::testing::_;
using ::testing::Return;

class MockOISInputManager : public InputManager
{
public:
    MockOISInputManager(const std::string&, std::pair<int,int>) {}
     
    void setKeyboardEventCallback(OIS::KeyListener&) {}
    void setMouseEventCallback(OIS::MouseListener&) {}  
    void capture() {}
};

class OISControllerTest : public ::testing::Test
{
public:
    OISControllerTest() {
        EXPECT_CALL(mockView, getViewportSize()).WillOnce(Return(size));
        EXPECT_CALL(mockView, windowHandle());
        EXPECT_CALL(mockView, setInputInspector(_));
    }
    ~OISControllerTest() {}
    MockView& View() { return mockView; }
    
private:
    MockView mockView;
    ViewportSize size;
};

TEST_F(OISControllerTest, initialization)
{        
    OISController<MockOISInputManager> controller(View());
}
