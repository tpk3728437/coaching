#ifndef MOCK_USERCOMMANDOBSERVER_H
#define MOCK_USERCOMMANDOBSERVER_H

#include <gmock/gmock.h>

class MockUserCommandObserver : public UserCommandObserver
{
public:
    MOCK_METHOD0(quitButtonPressed, void());
    MOCK_METHOD0(playButtonPressed, void());
    MOCK_METHOD0(doubleUpButtonPressed, void());
    MOCK_METHOD0(payoutButtonPressed, void());
};

#endif // MOCK_USERCOMMANDOBSERVER_H
