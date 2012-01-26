#ifndef COINFLIPLOGIC_H
#define COINFLIPLOGIC_H

#include "gameplay.h"

class CoinFlipLogic : public GamePlay
{
public:
    CoinFlipLogic();
    ~CoinFlipLogic();

private: // from GamePlay  
    void flip(FlipResult& result);
    
private:
    void onCoinFlippedTimerElapse();
    
private:
    FlipResult* mCoinFlipResultCallback;

};

#endif // COINFLIPLOGIC_H

