#include "graphics.h"
#include "timer.h"
#include "inputhandler.h"

Graphics::Graphics() : mShutDown(false)
{
    initializeOgre();
    createGorilla();
}

Graphics::~Graphics()
{
    std::cout << "\n** Average FPS is " << mWindow->getAverageFPS() << "\n\n";
    delete mSilverback;
    delete mRoot;
}

void Graphics::setInputInspector(InputInspector& inputInspector)
{
    mInputInspector = &inputInspector;
}

void Graphics::startRendering()
{
    mRoot->startRendering();
}
void Graphics::Quit()
{
    mShutDown = true;
}

ViewportSize Graphics::getViewportSize() const
{
     return ViewportSize(mViewport->getActualWidth(), mViewport->getActualHeight());
}

std::string Graphics::windowHandle() const
{
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;
    mWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    return windowHndStr.str();
}

Ogre::Viewport& Graphics::getViewport() const
{
    return *mViewport;
}

Gorilla::Silverback& Graphics::getSilverback() const
{
    return *mSilverback;
}

bool Graphics::frameStarted(const Ogre::FrameEvent& evt)
{
    ::Timer::getInstance()->processQueue();

    if (mWindow->isClosed() || mShutDown)
    {
        return false;
    }
    
    mInputInspector->Capture();

    return true;
}

void Graphics::initializeOgre()
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

void Graphics::createGorilla()
{
    mSilverback = new Gorilla::Silverback();
    mSilverback->loadAtlas("tripleflip");
    mSilverback->loadAtlas("background");
}
