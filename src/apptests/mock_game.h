#ifndef MOCK_GAME_H
#define MOCK_GAME_H

#include <gmock/gmock.h>
#include "headsortailsgame.h"


class MockGame : public Game
{
public:
    MOCK_METHOD0(Play, void());
};

#endif // MOCK_GAME_H
