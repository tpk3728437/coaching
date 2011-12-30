#ifndef MOCKUSEREVENTS_H
#define MOCKUSEREVENTS_H

#include <gmock/gmock.h>
#include "userevents.h"


class MockUserEvents : public UserEvents
{
public:
    MOCK_METHOD0(DoubleUp, bool());
};

#endif // MOCKUSEREVENTS_H
