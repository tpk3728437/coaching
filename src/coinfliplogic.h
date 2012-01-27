#ifndef COINFLIPLOGIC_H
#define COINFLIPLOGIC_H

#include "globals.h"

/**
 * This class is responsible for implementing the coin flipping
 * algorithm. Each call to the flip function will flip the coin
 * and return the result.
 */
class CoinFlipLogic
{
public:
    CoinFlipLogic();
    ~CoinFlipLogic();

    Side flip();
    
private:

};

#endif // COINFLIPLOGIC_H

