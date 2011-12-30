#ifndef MOCKGAMEPLAY_H
#define MOCKGAMEPLAY_H

#include "gameplay.h"


class MockGamePlay : public GamePlay
{
public:
    MOCK_CONST_METHOD1(Flip, void(FlipResult& result));
};

#endif // MOCKGAMEPLAY_H
