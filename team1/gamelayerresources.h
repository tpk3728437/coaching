#ifndef GAMELAYERRESOURCES_H
#define GAMELAYERRESOURCES_H

#include "Gorilla.h"


class GameLayerResources
{
public:
    GameLayerResources(Gorilla::Silverback& silverback, Ogre::Viewport& viewport);
    ~GameLayerResources();
    
    Gorilla::Screen& Screen();
    Gorilla::Sprite& CoinHead();
    Gorilla::Sprite& CoinTail();
    
    Gorilla::Sprite& BigwinText();
    Gorilla::Sprite& WinText();
    Gorilla::Sprite& LoseText();

private:

private:
    Gorilla::Screen*        mScreen;
    Gorilla::Layer*         mLayer;
    
    Gorilla::Sprite*        mCoinHeadSprite;
    Gorilla::Sprite*        mCoinTailSprite;
    
    Gorilla::Sprite* mBigWinSprite;
    Gorilla::Sprite* mWinSprite;
    Gorilla::Sprite* mLoseSprite;
};

#endif // GAMELAYERRESOURCES_H
