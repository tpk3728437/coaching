#ifndef MOCKGAMEPLAY_H
#define MOCKGAMEPLAY_H

#include "gameplay.h"


class MockGamePlay : public GamePlay
{
public:
    MOCK_METHOD1(flip, void(FlipResult& result));
};

#endif // MOCKGAMEPLAY_H
