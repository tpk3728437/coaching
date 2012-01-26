#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <OIS/OIS.h>
#include <memory>
#include "inputmanager.h"
#include "usercommandobserver.h"

/**
 * Interface for triggering the capturing of user input events.
 */
class InputInspector
{
public:
    virtual void capture() =0;
    
protected:
    virtual ~InputInspector() {}
};

/**
 * This class is responsible for capturing low-level user input events 
 * and relaying them as high-level command events through the  
 * UserCommandObserver interface.
 */
class InputHandler : public InputInspector, public OIS::KeyListener, public OIS::MouseListener
{
public:    
    InputHandler(std::auto_ptr<InputManager> inputManager, UserCommandObserver& observer);
    ~InputHandler();  

public: // from InputInspector
    void capture();
        
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
