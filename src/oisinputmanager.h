#ifndef OISINPUTMANAGER_H
#define OISINPUTMANAGER_H

#include "inputmanager.h"

/**
 * This class encapsulates the OIS related objects.
 */
class OISInputManager : public InputManager
{
public:    
    OISInputManager(const std::string& windowHandle, std::pair<int,int> viewportSize);
    ~OISInputManager();  

public: // from InputManager
    void setKeyboardEventCallback(OIS::KeyListener& listener);
    void setMouseEventCallback(OIS::MouseListener& listener);    
    void capture();
    
private:
    OIS::ParamList buildOISParameters(const std::string& windowHandle);
            
private:
    OIS::InputManager*      mInputManager;
    OIS::Keyboard*          mKeyboard;
    OIS::Mouse*             mMouse; 
};

#endif // OISINPUTMANAGER_H
