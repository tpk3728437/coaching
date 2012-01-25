#ifndef GAMELAYER_H
#define GAMELAYER_H

#include "gorilla.h"
#include "globals.h"

class GameLayerResources;
class GraphicsElement;

class GameLayer
{
public:
    GameLayer(GameLayerResources& resources);
    ~GameLayer();
    
    void ResetGraphics();
    void setCoinImage(int index, Side side);
    
    void showBigWin();
    void showWin();
    void showLoss();
    void showDoubleupQueryBoxes();

private:
    Gorilla::Screen& Screen();
    void createCoinRectangles();
    void createWinLogos();
    void createDoubleupBox();

private:
    Gorilla::Layer*         mLayer;
    GameLayerResources&     mResources;
    GraphicsElement*        mLogo;
        
    typedef std::vector<Gorilla::Rectangle*> RectangleVector;
    RectangleVector mCoinRectangles;
    
    Gorilla::Rectangle* mResultRect;
    
    GraphicsElement* mDoubleUp;
};

#endif // GAMELAYER_H
