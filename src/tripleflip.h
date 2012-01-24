#ifndef TRIPLEFLIP_H
#define TRIPLEFLIP_H

#include "coinfliplogic.h"
#include "oisinputmanager.h"
#include "oiscontroller.h"

class HeadsOrTailsGame;
class ViewInterface;

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

    typedef OISController<OISInputManager> AppController;
    AppController*          mController;
    HeadsOrTailsGame*       mGameEngine; 
    ViewInterface*          mView;
};

#endif // TRIPLEFLIP_H
