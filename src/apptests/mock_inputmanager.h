#ifndef MOCK_INPUTMANAGER_H
#define MOCK_INPUTMANAGER_H

#include <gmock/gmock.h>

class MockInputManager : public InputManager
{
public:
    MOCK_METHOD1(setKeyboardEventCallback, void(OIS::KeyListener& listener));
    MOCK_METHOD1(setMouseEventCallback, void(OIS::MouseListener& listener));
    MOCK_METHOD0(capture, void());
};

#endif // MOCK_INPUTMANAGER_H
