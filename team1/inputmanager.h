#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <OIS/OIS.h>

class InputManager
{
public:    
    virtual ~InputManager() {}
    virtual void setKeyboardEventCallback(OIS::KeyListener& listener) =0;
    virtual void setMouseEventCallback(OIS::MouseListener& listener) =0;    
    virtual void Capture() =0;
};

#endif // INPUTMANAGER_H
