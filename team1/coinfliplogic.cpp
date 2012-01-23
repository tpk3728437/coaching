#include "coinfliplogic.h"
#include "timer.h"
#include <tr1/functional>

CoinFlipLogic::CoinFlipLogic() :
    mCoinFlipResultCallback(0)
{
    srand(time(NULL));
}

CoinFlipLogic::~CoinFlipLogic()
{
}

void CoinFlipLogic::Flip(FlipResult& result)
{
    // save the interface
    mCoinFlipResultCallback = &result;
    
    std::tr1::function<void ()> callback(std::tr1::bind(&CoinFlipLogic::onCoinFlippedTimerElapse, this));
    
    ::Timer::getInstance()->delay(callback, 1000);
}

void CoinFlipLogic::onCoinFlippedTimerElapse() 
{ 
    // random
    Side side = (Side) (rand() % 2);

    mCoinFlipResultCallback->flipResult(side);
}
