#ifndef GAMELAYER_H
#define GAMELAYER_H

#include "Gorilla.h"
#include "globals.h"

class GameLayerResources;

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
    void createDoubleupBoxes();

private:
    Gorilla::Layer*         mLayer;
    GameLayerResources&     mResources;
    Gorilla::Sprite*        mLogoSprite;
        
    typedef std::vector<Gorilla::Rectangle*> RectangleVector;
    RectangleVector mCoinRectangles;
    
    Gorilla::Rectangle* mResultRect;
    
    Gorilla::Rectangle* mYesBoxRect;
    Gorilla::Rectangle* mNoBoxRect;
};

#endif // GAMELAYER_H
