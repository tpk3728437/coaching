#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <OIS/OIS.h>
#include <memory>
#include "inputmanager.h"

class UserCommandObserver
{
public:
    virtual void QuitButtonPressed() =0;
    virtual void PlayButtonPressed() =0;
    virtual void DoubleUpButtonPressed() =0;
    virtual void PayoutButtonPressed() =0;
};

class InputInspector
{
public:
    virtual void Capture() =0;

protected:
    virtual ~InputInspector() {}
};

class InputHandler : public InputInspector, public OIS::KeyListener, public OIS::MouseListener
{
public:    
    InputHandler(std::auto_ptr<InputManager> inputManager, UserCommandObserver& observer);
    ~InputHandler();  

public: // from InputInspector
    void Capture();
        
private:
    bool keyPressed( const OIS::KeyEvent &e );
    bool keyReleased( const OIS::KeyEvent &e );
    bool mouseMoved( const OIS::MouseEvent &arg );
    bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    
private:
    std::auto_ptr<InputManager> mInputManager;
    UserCommandObserver& mObserver;
};

#endif // INPUTHANDLER_H
