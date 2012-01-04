#ifndef GAMELAYER_H
#define GAMELAYER_H

#include "Gorilla.h"
#include "globals.h"

class GameLayerResources;

class GameLayer
{
public:
    GameLayer(Gorilla::Silverback& silverback, Ogre::Viewport& viewport, GameLayerResources& resources);
    ~GameLayer();
    
    void ResetGraphics();
    void setCoinImage(int index, Side side);
    
    void showBigWin();
    void showWin();
    void showLoss();

private:
    Gorilla::Screen& Screen();
    void createCoinSprites();
    void createWinLogos();

private:
    Gorilla::Layer*         mLayer;
    GameLayerResources&     mResources;
        
    typedef std::vector<Gorilla::Rectangle*> RectangleVector;
    RectangleVector mCoinRectangles;
    
    Gorilla::Rectangle* mResultRect;
    Gorilla::Sprite* mLoseSprite;
    Gorilla::Sprite* mWinSprite;
    Gorilla::Sprite* mBigwinSprite;
};

#endif // GAMELAYER_H
