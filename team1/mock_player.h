#ifndef MOCKPLAYER_H
#define MOCKPLAYER_H

#include <gmock/gmock.h>
#include "player.h"


class MockPlayer : public Player
{
public:
    MOCK_METHOD0(onPlayStarted, void());
    MOCK_METHOD2(onCoinFlipped, void(int index, Side side));
    MOCK_METHOD0(onGameWin, void());
    MOCK_METHOD0(onGameLoss, void());
    MOCK_METHOD0(onGameEnd, void());
};

#endif // MOCKPLAYER_H
