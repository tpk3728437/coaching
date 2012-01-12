#include "tripleflip.h"
#include "graphics.h"
#include "backgroundlayer.h"
#include "gamelayer.h"
#include "doubleuplayer.h"
#include "gamelayerresources.h"
#include "oisinputmanager.h"
#include <memory>
#include <utility>

TripleFlipApp::TripleFlipApp()
{
    createTripleFlipEngine();    
    initializeGraphics();
    initializeInputHandler();
    createLayers();
}
  
TripleFlipApp::~TripleFlipApp()
{
    delete mGameEngine;
    delete mDoubleupLayer;
    delete mGameLayer;
    delete mBackgroundLayer;
    delete mInputHandler;
    delete mGraphics;
}
  
void TripleFlipApp::start()
{
    mGraphics->startRendering();
    std::cout << "ended rendering" << std::endl;
}

void TripleFlipApp::initializeGraphics()
{
    mGraphics = new Graphics();
}

void TripleFlipApp::initializeInputHandler()
{
    ViewportSize size = mGraphics->getViewportSize();
    std::auto_ptr<InputManager> inputManager(new OISInputManager(mGraphics->getWindow(), size));
    mInputHandler = new InputHandler(inputManager, *this);
    
    mGraphics->setInputInspector(*mInputHandler);
}

void TripleFlipApp::createLayers()
{
    createBackgroundLayer();
    
    createGameLayerResources();
    createGameLayer();
    createDoubleupLayer();
}

void TripleFlipApp::createGameLayerResources()
{
    mGameResources = new GameLayerResources(mGraphics->getSilverback(), mGraphics->getViewport());
}

void TripleFlipApp::createBackgroundLayer()
{
    mBackgroundLayer = new BackgroundLayer(mGraphics->getSilverback(), mGraphics->getViewport());
}

void TripleFlipApp::createGameLayer()
{
    mGameLayer = new GameLayer(*mGameResources);
}

void TripleFlipApp::createDoubleupLayer()
{
    mDoubleupLayer = new DoubleupLayer(*mGameResources);
}

void TripleFlipApp::createTripleFlipEngine()
{
    mGameEngine = new HeadsOrTailsGame(mCoinFlipLogic, *this, mDoubleupLogic);
}

void TripleFlipApp::onPlayStarted()
{
    std::cout << "play started" << std::endl;
}

void TripleFlipApp::onCoinFlipped(int index, Side side)
{
    if (index >= 0 && index <= 2)
    {
        std::cout << "Coin flipped:" << index << " " << side << std::endl;
        mGameLayer->setCoinImage(index, side);
    }
    else
    {
        // double up rounds
        std::cout << "doubleUP result" << side << std::endl;
        mDoubleupLayer->SetCoin(side);
    }
}

void TripleFlipApp::onBigWin()
{
    mGameLayer->showBigWin();
}

void TripleFlipApp::onGameWin()
{
    mDoubleupLayer->Show();
}

void TripleFlipApp::onGameLoss()
{
    if (!mDoubleupLayer->IsVisible())
    {
        mGameLayer->showLoss();
    }
}

void TripleFlipApp::onGameEnd()
{
    std::cout << "play end" << std::endl;
}

void TripleFlipApp::onDoubleUp(bool win)
{
    mDoubleupLayer->Result(win);
}

void TripleFlipApp::QuitButtonPressed()
{
    mGraphics->Quit();
}

void TripleFlipApp::PlayButtonPressed()
{
    mDoubleupLayer->Hide();
    mGameLayer->ResetGraphics();
    mGameEngine->Play();          
}

void TripleFlipApp::DoubleUpButtonPressed()
{
    mDoubleupLogic.DoubleUp();
}

void TripleFlipApp::PayoutButtonPressed()
{
    mDoubleupLogic.CashOut();
}
