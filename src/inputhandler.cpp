#include "inputhandler.h"
#include <iostream>

InputHandler::InputHandler(std::auto_ptr<InputManager> inputManager, UserCommandObserver& observer) :
    mInputManager(inputManager), mObserver(observer)
{
    mInputManager->setKeyboardEventCallback(*this);
    mInputManager->setMouseEventCallback(*this);    
}

InputHandler::~InputHandler()
{
}

void InputHandler::capture()
{
    mInputManager->capture();
}

bool InputHandler::keyPressed( const OIS::KeyEvent &e )
{
    if (e.key == OIS::KC_ESCAPE)
    {   
        mObserver.quitButtonPressed();
    }    
    if (e.key == OIS::KC_P)
    {
        mObserver.playButtonPressed();
    }
    if (e.key == OIS::KC_Y) 
    {
        mObserver.doubleUpButtonPressed();
    }
    if (e.key == OIS::KC_N)
    {
        mObserver.payoutButtonPressed();
    }

    return true;
}

bool InputHandler::keyReleased( const OIS::KeyEvent& /*e*/ )
{
    return true;
}

bool InputHandler::mouseMoved( const OIS::MouseEvent& /*arg*/ )
{
    return true;
}

bool InputHandler::mousePressed( const OIS::MouseEvent& /*arg*/, OIS::MouseButtonID /*id*/ )
{
    return true;
}

bool InputHandler::mouseReleased( const OIS::MouseEvent& /*arg*/, OIS::MouseButtonID /*id*/ )
{
    return true;
}
