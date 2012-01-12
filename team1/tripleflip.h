#ifndef TRIPLEFLIP_H
#define TRIPLEFLIP_H

#include "coinfliplogic.h"

class Controller;
class HeadsOrTailsGame;
class View;

class TripleFlipApp
{
public:
    TripleFlipApp();
    ~TripleFlipApp();  
    void start();
      
private:
    CoinFlipLogic           mCoinFlipLogic;

    Controller*             mController;
    HeadsOrTailsGame*       mGameEngine; 
    View*                   mView;
};

#endif // TRIPLEFLIP_H
