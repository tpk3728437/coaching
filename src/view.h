#ifndef VIEW_H
#define VIEW_H

#include "viewinterface.h"

class Graphics;
class BackgroundLayer;
class GameLayer;
class DoubleupLayer;
class GameLayerResources;

/**
 * This class is responsible for displaying the application
 * user interface.
 */
class View : public ViewInterface
{
public:
    View();
    ~View();

public: // from ViewInterface
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
    Graphics*               mGraphics;
    BackgroundLayer*        mBackgroundLayer;
    GameLayerResources*     mGameResources;
    GameLayer*              mGameLayer;
    DoubleupLayer*          mDoubleupLayer;    
};

#endif // VIEW_H