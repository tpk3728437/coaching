#ifndef OISCONTROLLER_H
#define OISCONTROLLER_H

#include "controller.h"
#include "inputhandler.h"
#include "view.h"

/**
 * Controller that uses OIS for input.
 */
template<typename T_OISInputManager>
class OISController : public Controller
{
public:
    OISController(ViewInterface& view);
    ~OISController();

private:
    void initializeInputHandler();
    
private:
    InputHandler*           mInputHandler;
};

template<typename T_OISInputManager> 
OISController<T_OISInputManager>::OISController(ViewInterface& view) : Controller(view), mInputHandler(0)
{
    initializeInputHandler();
}

template<typename T_OISInputManager> 
OISController<T_OISInputManager>::~OISController()
{
    delete mInputHandler;
}

template<typename T_OISInputManager> 
void OISController<T_OISInputManager>::initializeInputHandler()
{
    ViewportSize size = mView.getViewportSize();
    std::auto_ptr<InputManager> inputManager(new T_OISInputManager(mView.windowHandle(), size));
    mInputHandler = new InputHandler(inputManager, *this);
    
    mView.setInputInspector(*mInputHandler);
}

#endif // OISCONTROLLER_H
