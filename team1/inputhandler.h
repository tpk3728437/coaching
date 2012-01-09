#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <OIS/OIS.h>

class UserCommandObserver
{
public:
    virtual void QuitButtonPressed() =0;
    virtual void PlayButtonPressed() =0;
    virtual void DoubleUpButtonPressed() =0;
    virtual void PayoutButtonPressed() =0;
};

class InputHandler : public OIS::KeyListener, public OIS::MouseListener
{
public:    
    InputHandler(OIS::ParamList params, int viewPortWidth, int viewPortHeight, UserCommandObserver& observer);
    ~InputHandler();  
    
    void Capture();
        
private:
    bool keyPressed( const OIS::KeyEvent &e );
    bool keyReleased( const OIS::KeyEvent &e );
    bool mouseMoved( const OIS::MouseEvent &arg );
    bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    
private:
    OIS::InputManager*      mInputManager;
    OIS::Keyboard*          mKeyboard;
    OIS::Mouse*             mMouse; 
    
    UserCommandObserver& mObserver;
};

#endif // INPUTHANDLER_H
