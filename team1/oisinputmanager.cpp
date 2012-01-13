#include "oisinputmanager.h"

OISInputManager::OISInputManager(const std::string& windowHandle, std::pair<int,int> viewportSize)
{
    OIS::ParamList params = buildOISParameters(windowHandle);
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

OIS::ParamList OISInputManager::buildOISParameters(const std::string& windowHandle)
{
    OIS::ParamList pl;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHandle));
    return pl;
}
