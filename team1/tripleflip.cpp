#include "tripleflip.h"
#include <sstream>
#include "timer.h"
#include "backgroundlayer.h"
#include "gamelayer.h"
#include "doubleuplayer.h"


TripleFlipApp::TripleFlipApp()
{
    initializeOgre();
    initializeOIS();

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

    if (mWindow->isClosed())
    {
        return false;
    }
    
    mKeyboard->capture();
    if (mKeyboard->isKeyDown(OIS::KC_ESCAPE))
    {
        return false;
    }
    
    mMouse->capture();
    return true;
}
  
bool TripleFlipApp::keyPressed( const OIS::KeyEvent &e )
{
    if (e.key == OIS::KC_P)   // P = play
    {
        play();
    }
    if (e.key == OIS::KC_Y) // double up
    {
        mDoubleupLogic.DoubleUp();
    }
    if (e.key == OIS::KC_N) // no double uo
    {
        mDoubleupLogic.CashOut();
    }

    return true;
}

bool TripleFlipApp::keyReleased( const OIS::KeyEvent &e )
{
    return true;
}

bool TripleFlipApp::mouseMoved( const OIS::MouseEvent &arg )
{
    return true;
}

bool TripleFlipApp::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    return true;
}

bool TripleFlipApp::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
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
  
void TripleFlipApp::initializeOIS()
{
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;
    mWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

    mInputManager = OIS::InputManager::createInputSystem( pl );

    mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, true));
    mKeyboard->setEventCallback(this);

    mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(OIS::OISMouse, true));
    mMouse->setEventCallback(this);
    mMouse->getMouseState().width = mViewport->getActualWidth();
    mMouse->getMouseState().height = mViewport->getActualHeight();
}

void TripleFlipApp::createGorilla()
{
    mSilverback = new Gorilla::Silverback();
}

void TripleFlipApp::createLayers()
{
    createBackgroundLayer();
    createGameLayer();
    createDoubleupLayer();
}

void TripleFlipApp::createBackgroundLayer()
{
    mBackgroundLayer = new BackgroundLayer(*mSilverback, *mViewport);
}

void TripleFlipApp::createGameLayer()
{
    mGameLayer = new GameLayer(*mSilverback, *mViewport);
}

void TripleFlipApp::createDoubleupLayer()
{
    mDoubleupLayer = new DoubleupLayer(*mSilverback, *mViewport);
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
    mGameLayer->showWin();
}

void TripleFlipApp::onGameLoss()
{
    mGameLayer->showLoss();
}

void TripleFlipApp::onGameEnd()
{
    std::cout << "play end" << std::endl;
}

void TripleFlipApp::onDoubleUp(bool win)
{
    mDoubleupLayer->Show();
}

void TripleFlipApp::play()
{
    std::cout << "play started" << std::endl;

    mDoubleupLayer->Hide();
    mGameLayer->ResetGraphics();
    mGameEngine->Play();      
}
