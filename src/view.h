#ifndef VIEW_H
#define VIEW_H

#include "viewinterface.h"

class Graphics;
class BackgroundLayer;
class GameLayer;
class DoubleupLayer;
class LayerFactory;

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
    void quit();
    void setInputInspector(InputInspector& inputInspector);
    
    void resetGraphics();
    void showDoubleUpScreen();
    void resetDoubleUpScreenGraphics();
    void showDoubleupResult(bool win);
    void showGameLoss();
    void showBigWin();
    void showBaseGameCoin(int index, Side side);
    void showDoubleUpCoin(Side side);
    
    ViewportSize getViewportSize() const;
    std::string windowHandle() const;
    
private:
    Graphics*               mGraphics;
    BackgroundLayer*        mBackgroundLayer;
    LayerFactory*           mLayerFactory;
    GameLayer*              mGameLayer;
    DoubleupLayer*          mDoubleupLayer;    
};

#endif // VIEW_H
