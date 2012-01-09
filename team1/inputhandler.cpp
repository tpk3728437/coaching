#include "inputhandler.h"

InputHandler::InputHandler(OIS::ParamList params, int viewPortWidth, int viewPortHeight, UserCommandObserver& observer) :
    mObserver(observer)
{
    mInputManager = OIS::InputManager::createInputSystem( params );

    mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, true));
    mKeyboard->setEventCallback(this);

    mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(OIS::OISMouse, true));
    mMouse->setEventCallback(this);
    mMouse->getMouseState().width = viewPortWidth; 
    mMouse->getMouseState().height = viewPortHeight;
}

InputHandler::~InputHandler()
{
}

void InputHandler::Capture()
{
    mKeyboard->capture();
    mMouse->capture();
}

bool InputHandler::keyPressed( const OIS::KeyEvent &e )
{
    if (e.key == OIS::KC_ESCAPE)
    {   
        mObserver.QuitButtonPressed();
    }    
    if (e.key == OIS::KC_P)
    {
        mObserver.PlayButtonPressed();
    }
    if (e.key == OIS::KC_Y) 
    {
        mObserver.DoubleUpButtonPressed();
    }
    if (e.key == OIS::KC_N)
    {
        mObserver.PayoutButtonPressed();
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
