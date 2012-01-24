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
    virtual void Quit() =0;   
    virtual void setInputInspector(InputInspector& inputInspector) =0;
    
    virtual void ResetGraphics() =0;
    virtual void ShowDoubleUpScreen() =0;
    virtual void ResetDoubleUpScreenGraphics() =0;
    virtual void ShowDoubleupResult(bool win) =0;
    virtual void ShowGameLoss() =0;
    virtual void ShowBigWin() =0;
    virtual void ShowBaseGameCoin(int index, Side side) =0;
    virtual void ShowDoubleUpCoin(Side side) =0;
    
    virtual ViewportSize getViewportSize() const =0;
    virtual std::string windowHandle() const =0;
};

#endif // VIEWINTERFACE_H
