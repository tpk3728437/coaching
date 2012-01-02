#include "tripleflip.h"
#include <sstream>
#include <boost/function.hpp>
#include "timer.h"

TripleFlipApp::TripleFlipApp() : mNextUpdate(0), mCoinFlipResultCallback(0)
{
    srand(time(NULL));

    initializeOgre();
    initializeOIS();

    // Create Silverback and load in tripleflip
    mSilverback = new Gorilla::Silverback();
    mSilverback->loadAtlas("tripleflip");
    mSilverback->loadAtlas("background");

    createBackground();
    
    mScreen = mSilverback->createScreen(mViewport, "tripleflip");
    mScreen->setOrientation(Ogre::OR_PORTRAIT);
    Ogre::Real vpWidth = mScreen->getWidth(); 
    Ogre::Real vpHeight = mScreen->getHeight();

    // Create our drawing layer
    mLayer = mScreen->createLayer(1);
    caption = mLayer->createCaption(24, 0, 5, "Three flip");
    caption->width(vpWidth);
    caption->align(Gorilla::TextAlign_Centre);
    
    createCoinSprites();
    
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
        std::cout << "play started" << std::endl;
        mGameEngine->Play();            
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

void TripleFlipApp::createCoinSprites()
{
    mCoinHeadSprite = mScreen->getAtlas()->getSprite("coinhead");
    mCoinTailSprite = mScreen->getAtlas()->getSprite("cointail");
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
    if (index == 0)
    {
        setCoinImage(side, Ogre::Vector2(100,300));
    }
    else if (index == 1)
    {
        setCoinImage(side, Ogre::Vector2(400,300));
    }
    else if (index == 2)
    {
        setCoinImage(side, Ogre::Vector2(700,300));
    }
    else
    {
        // double up rounds
        std::cout << "doubleUP result" << side << std::endl;
    }
}

void TripleFlipApp::onBigWin()
{
    std::cout << "BIG WIN!!!" << std::endl;

    caption = mLayer->createCaption(24, 0, 700, "BIG WIN!!");
    caption->width(500);
    caption->align(Gorilla::TextAlign_Centre);
}

void TripleFlipApp::onGameWin()
{
    std::cout << "WIN" << std::endl;

    caption = mLayer->createCaption(24, 0, 700, "WIN!!");
    caption->width(500);
    caption->align(Gorilla::TextAlign_Centre);
}

void TripleFlipApp::onGameLoss()
{
    std::cout << "LOSE" << std::endl;

    caption = mLayer->createCaption(24, 0, 700, "lose");
    caption->width(500);
    caption->align(Gorilla::TextAlign_Centre);
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

void TripleFlipApp::setCoinImage(Side side, Ogre::Vector2 position)
{
    Ogre::Vector2 coinSize(mCoinHeadSprite->spriteWidth, mCoinHeadSprite->spriteHeight);
    Gorilla::Rectangle* coinRect = mLayer->createRectangle(position, coinSize);
    if (side == Heads) 
    {
        coinRect->background_image(mCoinHeadSprite);
    }
    else 
    {
        coinRect->background_image(mCoinTailSprite);
    }
}

void TripleFlipApp::createBackground()
{
    mBackgroundScreen = mSilverback->createScreen(mViewport, "background");
    mBackgroundScreen->setOrientation(Ogre::OR_PORTRAIT);
    Ogre::Real vpWidth = mBackgroundScreen->getWidth(); 
    Ogre::Real vpHeight = mBackgroundScreen->getHeight();

    // Create our drawing layer
    mBackgroundLayer = mBackgroundScreen->createLayer(0);
    rect = mBackgroundLayer->createRectangle(0,0, vpWidth, vpHeight);
    //rect->background_gradient(Gorilla::Gradient_Diagonal, Gorilla::rgb(198,229,209), Gorilla::rgb(255,180,174));
    rect->background_image("background");
}
