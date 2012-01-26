#ifndef VIEWINTERFACE_H
#define VIEWINTERFACE_H

#include "globals.h"
#include "uitypes.h"
#include <string>

class InputInspector;

class ViewInterface
{
public:
    virtual ~ViewInterface() {}
    virtual void startRendering() =0; 
    virtual void quit() =0;   
    virtual void setInputInspector(InputInspector& inputInspector) =0;
    
    virtual void resetGraphics() =0;
    virtual void showDoubleUpScreen() =0;
    virtual void resetDoubleUpScreenGraphics() =0;
    virtual void showDoubleupResult(bool win) =0;
    virtual void showGameLoss() =0;
    virtual void showBigWin() =0;
    virtual void showBaseGameCoin(int index, Side side) =0;
    virtual void showDoubleUpCoin(Side side) =0;
    
    virtual ViewportSize getViewportSize() const =0;
    virtual std::string windowHandle() const =0;
};

#endif // VIEWINTERFACE_H
