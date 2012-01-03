#include "tripleflip.h"
#include <sstream>
#include <boost/function.hpp>
#include "timer.h"

TripleFlipApp::TripleFlipApp() : 
    mCoinFlipResultCallback(0)
{
    srand(time(NULL));

    initializeOgre();
    initializeOIS();

    createGorilla();

    createBackground();

    createGameScreen();
    
    createCoinSprites();
    
    createWinLogos();
    
    createTripleFlipEngine();
}
  
TripleFlipApp::~TripleFlipApp()
{
    std::cout << "\n** Average FPS is " << mWindow->getAverageFPS() << "\n\n";
    delete mGameEngine;
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
    srand(time(0));

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
    mSilverback->loadAtlas("tripleflip");
    mSilverback->loadAtlas("background");
}

void TripleFlipApp::createBackground()
{
    mBackgroundScreen = mSilverback->createScreen(mViewport, "background");
    mBackgroundScreen->setOrientation(Ogre::OR_PORTRAIT);
    Ogre::Real vpWidth = mBackgroundScreen->getWidth(); 
    Ogre::Real vpHeight = mBackgroundScreen->getHeight();

    mBackgroundLayer = mBackgroundScreen->createLayer(0);
    Gorilla::Rectangle* backgroundRect = mBackgroundLayer->createRectangle(0,0, vpWidth, vpHeight);
    backgroundRect->background_image("background");
}

void TripleFlipApp::createGameScreen()
{
    mScreen = mSilverback->createScreen(mViewport, "tripleflip");
    mScreen->setOrientation(Ogre::OR_PORTRAIT);
    Ogre::Real vpWidth = mScreen->getWidth(); 
    Ogre::Real vpHeight = mScreen->getHeight();

    mLayer = mScreen->createLayer(1);    
    Gorilla::Sprite* logoSprite = mScreen->getAtlas()->getSprite("logo"); 
    Gorilla::Rectangle* logoRect = mLayer->createRectangle(100,0, logoSprite->spriteWidth, logoSprite->spriteHeight);
    logoRect->background_image(logoSprite);
}

void TripleFlipApp::createCoinSprites()
{
    mCoinHeadSprite = mScreen->getAtlas()->getSprite("coinhead");
    mCoinTailSprite = mScreen->getAtlas()->getSprite("cointail");
    
    for (int i = 0; i <= 2; ++i)
    {
        const int horizontalPosition = 100 + i * 300;
        const Ogre::Vector2 coinSize(mCoinHeadSprite->spriteWidth, mCoinHeadSprite->spriteHeight);    
        
        Gorilla::Rectangle* coinRect = mLayer->createRectangle(Ogre::Vector2(horizontalPosition,300), coinSize);
        coinRect->background_image("opaque");
        mCoinRectangles.push_back(coinRect);
    }
}

void TripleFlipApp::createWinLogos()
{
    mLoseSprite = mScreen->getAtlas()->getSprite("lose"); 
    mWinSprite = mScreen->getAtlas()->getSprite("win"); 
    mBigwinSprite = mScreen->getAtlas()->getSprite("bigwin"); 

    Ogre::Real vpHeight = mScreen->getHeight();
    mResultRect = mLayer->createRectangle(100,vpHeight-200, mBigwinSprite->spriteWidth, mWinSprite->spriteHeight);
    mResultRect->background_image("opaque");
}

void TripleFlipApp::createTripleFlipEngine()
{
    mGameEngine = new HeadsOrTailsGame(*this, *this, *this);
}

void TripleFlipApp::onCoinFlippedTimerElapse() 
{ 
    // random
    Side side = (Side) (rand() % 2);

    mCoinFlipResultCallback->flipResult(side);
}

void TripleFlipApp::Flip(FlipResult& result)
{
    // save the interface
    mCoinFlipResultCallback = &result;
    
    boost::function<void ()> callback(boost::bind(&TripleFlipApp::onCoinFlippedTimerElapse, this));
    
    ::Timer::getInstance()->delay(callback, 1000);
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
        setCoinImage(index, side);
    }
    else
    {
        // double up rounds
        std::cout << "doubleUP result" << side << std::endl;
    }
}

void TripleFlipApp::onBigWin()
{
    mResultRect->background_image(mBigwinSprite);
}

void TripleFlipApp::onGameWin()
{
    mResultRect->background_image(mWinSprite);
}

void TripleFlipApp::onGameLoss()
{
    mResultRect->background_image(mLoseSprite);
}

void TripleFlipApp::onGameEnd()
{
    std::cout << "play end" << std::endl;
}

void TripleFlipApp::onDoubleUp(bool win)
{
}

bool TripleFlipApp::DoubleUp()
{
    return false;
}

void TripleFlipApp::setCoinImage(int index, Side side)
{
    if (side == Heads) 
    {
        std::cout << "coin rect addr:" << mCoinRectangles[index] << std::endl;
        mCoinRectangles[index]->background_image(mCoinHeadSprite);
    }
    else 
    {
        mCoinRectangles[index]->background_image(mCoinTailSprite);
    }
}

void TripleFlipApp::play()
{
    std::cout << "play started" << std::endl;

    for (RectangleVector::iterator i = mCoinRectangles.begin(); i != mCoinRectangles.end(); ++i)
    {
        (*i)->background_image("opaque");
    }
    mResultRect->background_image("opaque");
    mGameEngine->Play();      
}
