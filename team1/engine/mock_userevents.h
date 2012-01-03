#ifndef MOCKUSEREVENTS_H
#define MOCKUSEREVENTS_H

#include <gmock/gmock.h>
#include "userevents.h"


class MockUserEvents : public UserEvents
{
public:
    MOCK_METHOD1(DoesUserWantToDoubleUp, void(DoubleupChoiceResult& result));
};

#endif // MOCKUSEREVENTS_H
