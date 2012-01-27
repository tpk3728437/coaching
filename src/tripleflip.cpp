#include "tripleflip.h"
#include "view.h"
#include "headsortailsgame.h"


TripleFlipApp::TripleFlipApp()
{
    mView = new View();
    mController = new AppController(*mView);
    mGameEngine = new HeadsOrTailsGame();    
    mController->setEngine(*mGameEngine);
}
  
TripleFlipApp::~TripleFlipApp()
{
    delete mGameEngine;
    delete mController;
    delete mView;
}
  
void TripleFlipApp::start()
{
    mView->startRendering();
}
