#include "gamelayerresources.h"

GameLayerResources::GameLayerResources(Gorilla::Silverback& silverback, Ogre::Viewport& viewport)
{
    silverback.loadAtlas("tripleflip");

    mScreen = silverback.createScreen(&viewport, "tripleflip");
    mScreen->setOrientation(Ogre::OR_PORTRAIT);
    
    mCoinHeadSprite = mScreen->getAtlas()->getSprite("coinhead");
    mCoinTailSprite = mScreen->getAtlas()->getSprite("cointail");

}

GameLayerResources::~GameLayerResources()
{
}

Gorilla::Screen& GameLayerResources::Screen()
{
    return *mScreen;
}

Gorilla::Sprite& GameLayerResources::CoinHead()
{
    return *mCoinHeadSprite;
}

Gorilla::Sprite& GameLayerResources::CoinTail()
{
    return *mCoinTailSprite;
}
