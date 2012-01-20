#include "tripleflip.h"
#include "view.h"
#include "HeadsOrTailsGame.h"


TripleFlipApp::TripleFlipApp()
{
    mView = new View();
    mController = new AppController(*mView);
    mGameEngine = new HeadsOrTailsGame(mCoinFlipLogic, *mController, mController->userEventsHandler());    
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
