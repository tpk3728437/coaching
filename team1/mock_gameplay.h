#ifndef MOCKGAMEPLAY_H
#define MOCKGAMEPLAY_H

#include "gameplay.h"

class MockGamePlay : public GamePlay
{
public:
    MOCK_CONST_METHOD0(Flip, int());
};

#endif // MOCKGAMEPLAY_H
