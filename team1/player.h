#ifndef PLAYER_H
#define PLAYER_H

#include "globals.h"

class Player
{
public:
    virtual void onPlayStarted() =0;
    virtual void onCoinFlipped(int index, Side side) =0;
    virtual void onBigWin() =0;
    virtual void onGameWin() =0;
    virtual void onGameLoss() =0;
    virtual void onGameEnd() =0;
    virtual void onDoubleUp(bool win) =0;
    
};

#endif // PLAYER_H
