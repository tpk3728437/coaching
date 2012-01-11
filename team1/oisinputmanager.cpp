#include "oisinputmanager.h"

OISInputManager::OISInputManager(Ogre::RenderWindow& window, std::pair<int,int> viewportSize)
{
    OIS::ParamList params = buildOISParameters(window);
    mInputManager = OIS::InputManager::createInputSystem( params );
    
    mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, true));

    mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(OIS::OISMouse, true));
    mMouse->getMouseState().width = viewportSize.first; 
    mMouse->getMouseState().height = viewportSize.second;
}

OISInputManager::~OISInputManager()
{
    if (mInputManager) 
    {
        mInputManager->destroyInputObject(mMouse);
        mInputManager->destroyInputObject(mKeyboard);
    }
    OIS::InputManager::destroyInputSystem(mInputManager);
}

void OISInputManager::setKeyboardEventCallback(OIS::KeyListener& listener)
{
    mKeyboard->setEventCallback(&listener);
}

void OISInputManager::setMouseEventCallback(OIS::MouseListener& listener)
{
    mMouse->setEventCallback(&listener);
}

void OISInputManager::Capture()
{
    mKeyboard->capture();
    mMouse->capture();
}

OIS::ParamList OISInputManager::buildOISParameters(Ogre::RenderWindow& window)
{
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;
    window.getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
    return pl;
}
