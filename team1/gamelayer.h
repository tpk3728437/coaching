#ifndef GAMELAYER_H
#define GAMELAYER_H

#include "Gorilla.h"
#include "globals.h"


class GameLayer
{
public:
    GameLayer(Gorilla::Silverback& silverback, Ogre::Viewport& viewport);
    ~GameLayer();
    
    void ResetGraphics();
    void setCoinImage(int index, Side side);
    
    void showBigWin();
    void showWin();
    void showLoss();

private:
    void createCoinSprites();
    void createWinLogos();

private:
    Gorilla::Screen*        mScreen;
    Gorilla::Layer*         mLayer;
    
    Gorilla::Sprite*        mCoinHeadSprite;
    Gorilla::Sprite*        mCoinTailSprite;
    
    typedef std::vector<Gorilla::Rectangle*> RectangleVector;
    RectangleVector mCoinRectangles;
    
    Gorilla::Rectangle* mResultRect;
    Gorilla::Sprite* mLoseSprite;
    Gorilla::Sprite* mWinSprite;
    Gorilla::Sprite* mBigwinSprite;
};

#endif // GAMELAYER_H
