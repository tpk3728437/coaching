#ifndef VIEW_H
#define VIEW_H

#include "graphics.h"
#include "globals.h"

class BackgroundLayer;
class GameLayer;
class DoubleupLayer;
class GameLayerResources;


class View
{
public:
    View();
    ~View();
    void startRendering(); 
    void Quit();   
    void setInputInspector(InputInspector& inputInspector);
    
    void ResetGraphics();
    void ShowDoubleUpScreen();
    void ResetDoubleUpScreenGraphics();
    void ShowDoubleupResult(bool win);
    void ShowGameLoss();
    void ShowBigWin();
    void ShowBaseGameCoin(int index, Side side);
    void ShowDoubleUpCoin(Side side);
    
    ViewportSize getViewportSize() const;
    std::string windowHandle() const;
    
private:
    void initializeGraphics();
    void createLayers();
    void createGameLayerResources();
    void createBackgroundLayer();
    void createGameLayer();
    void createDoubleupLayer();

private:
    Graphics*               mGraphics;
    BackgroundLayer*        mBackgroundLayer;
    GameLayerResources*     mGameResources;
    GameLayer*              mGameLayer;
    DoubleupLayer*          mDoubleupLayer;    
};

#endif // VIEW_H
