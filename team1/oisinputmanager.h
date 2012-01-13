#ifndef OISINPUTMANAGER_H
#define OISINPUTMANAGER_H

#include "inputmanager.h"
#include <OGRE/Ogre.h>
#include <utility>

class OISInputManager : public InputManager
{
public:    
    OISInputManager(const std::string& windowHandle, std::pair<int,int> viewportSize);
    ~OISInputManager();  

public: // from InputManager
    void setKeyboardEventCallback(OIS::KeyListener& listener);
    void setMouseEventCallback(OIS::MouseListener& listener);    
    void Capture();
    
private:
    OIS::ParamList buildOISParameters(const std::string& windowHandle);
            
private:
    OIS::InputManager*      mInputManager;
    OIS::Keyboard*          mKeyboard;
    OIS::Mouse*             mMouse; 
};

#endif // OISINPUTMANAGER_H
