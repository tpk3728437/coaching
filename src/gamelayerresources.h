#ifndef GAMELAYERRESOURCES_H
#define GAMELAYERRESOURCES_H

#include "gorilla.h"


class GameLayerResources
{
public:
    GameLayerResources(Gorilla::Silverback& silverback, Ogre::Viewport& viewport);
    ~GameLayerResources();
    
    Gorilla::Layer* CreateLayer(int order);
    
    Gorilla::Screen& Screen();
    Gorilla::Sprite& CoinHead();
    Gorilla::Sprite& CoinTail();
    
    Gorilla::Sprite& BigwinText();
    Gorilla::Sprite& WinText();
    Gorilla::Sprite& LoseText();
    
    Gorilla::Sprite& DoubleupText();

private:
    Gorilla::Screen*        mScreen;

    Gorilla::Sprite* mCoinHeadSprite;
    Gorilla::Sprite* mCoinTailSprite;
    
    Gorilla::Sprite* mBigWinSprite;
    Gorilla::Sprite* mWinSprite;
    Gorilla::Sprite* mLoseSprite;
    
    Gorilla::Sprite* mDoubleupSprite;
};

#endif // GAMELAYERRESOURCES_H
