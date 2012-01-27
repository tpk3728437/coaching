#include "coinfliplogic.h"
#include <stdlib.h>
#include <time.h>

CoinFlipLogic::CoinFlipLogic()
{
    srand(time(NULL));
}

CoinFlipLogic::~CoinFlipLogic()
{
}

Side CoinFlipLogic::flip()
{
    // random
    Side side = (Side) (rand() % 2);
    return side;
}
