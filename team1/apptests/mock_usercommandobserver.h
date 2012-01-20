#ifndef MOCK_USERCOMMANDOBSERVER_H
#define MOCK_USERCOMMANDOBSERVER_H

#include <gmock/gmock.h>

class MockUserCommandObserver : public UserCommandObserver
{
public:
    MOCK_METHOD0(QuitButtonPressed, void());
    MOCK_METHOD0(PlayButtonPressed, void());
    MOCK_METHOD0(DoubleUpButtonPressed, void());
    MOCK_METHOD0(PayoutButtonPressed, void());
};

#endif // MOCK_USERCOMMANDOBSERVER_H
