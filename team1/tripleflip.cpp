#include "tripleflip.h"
#include <sstream>
#include "timer.h"
#include "backgroundlayer.h"
#include "gamelayer.h"
#include "doubleuplayer.h"
#include "gamelayerresources.h"
#include "oisinputmanager.h"
#include <memory>
#include <utility>

TripleFlipApp::TripleFlipApp() : mShutDown(false)
{
    initializeOgre();
    
    initializeInputHandler();

    createGorilla();

    createLayers();
    
    createTripleFlipEngine();    
}
  
TripleFlipApp::~TripleFlipApp()
{
    std::cout << "\n** Average FPS is " << mWindow->getAverageFPS() << "\n\n";
    delete mGameEngine;
    delete mDoubleupLayer;
    delete mGameLayer;
    delete mBackgroundLayer;
    delete mInputHandler;
    delete mSilverback;
    delete mRoot;
}
  
void TripleFlipApp::start()
{
    mRoot->startRendering();
}
  
bool TripleFlipApp::frameStarted(const Ogre::FrameEvent& evt)
{
    ::Timer::getInstance()->processQueue();

    if (mWindow->isClosed() || mShutDown)
    {
        return false;
    }
    
    mInputHandler->Capture();

    return true;
}

void TripleFlipApp::initializeOgre()
{
    mRoot = new Ogre::Root("","");
    mRoot->addFrameListener(this);

    mRoot->loadPlugin(OGRE_RENDERER);

    mRoot->setRenderSystem(mRoot->getAvailableRenderers()[0]);

    Ogre::ResourceGroupManager* rgm = Ogre::ResourceGroupManager::getSingletonPtr();
    rgm->addResourceLocation(".", "FileSystem");

    mRoot->initialise(false);

    mWindow = mRoot->createRenderWindow("Gorilla", 1024, 768, false);
    mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
    mCamera = mSceneMgr->createCamera("Camera");
    mViewport = mWindow->addViewport(mCamera);
    mViewport->setBackgroundColour(Gorilla::webcolour(Gorilla::Colours::FireBrick));

    rgm->initialiseAllResourceGroups();
}
  
void TripleFlipApp::initializeInputHandler()
{
    std::pair<int,int> viewportSize(mViewport->getActualWidth(), mViewport->getActualHeight());
    std::auto_ptr<InputManager> inputManager(new OISInputManager(*mWindow, viewportSize));
    mInputHandler = new InputHandler(inputManager, *this);
}

void TripleFlipApp::createGorilla()
{
    mSilverback = new Gorilla::Silverback();
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
    mGameResources = new GameLayerResources(*mSilverback, *mViewport);
}

void TripleFlipApp::createBackgroundLayer()
{
    mBackgroundLayer = new BackgroundLayer(*mSilverback, *mViewport);
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
    mShutDown = true;
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
