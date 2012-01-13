#ifndef TRIPLEFLIP_H
#define TRIPLEFLIP_H

#include "coinfliplogic.h"

class Controller;
class HeadsOrTailsGame;
class View;

/**
 * Triple flip application class. Application uses
 * Model-View-Controller architecture.
 * 
 * Calling the start function will start the main
 * event loop and waits until the application quits. 
 */
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
