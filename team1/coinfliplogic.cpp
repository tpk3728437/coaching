#include "coinfliplogic.h"
#include "timer.h"
#include <boost/function.hpp>


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
    
    boost::function<void ()> callback(boost::bind(&CoinFlipLogic::onCoinFlippedTimerElapse, this));
    
    ::Timer::getInstance()->delay(callback, 1000);
}

void CoinFlipLogic::onCoinFlippedTimerElapse() 
{ 
    // random
    Side side = (Side) (rand() % 2);

    mCoinFlipResultCallback->flipResult(side);
}
