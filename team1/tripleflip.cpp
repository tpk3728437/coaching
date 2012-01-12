#include "tripleflip.h"
#include "controller.h"
#include "view.h"
#include "HeadsOrTailsGame.h"
#include <utility>


TripleFlipApp::TripleFlipApp()
{
    mView = new View();
    mController = new Controller(*mView);
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
