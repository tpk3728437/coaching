#include "gamelayerresources.h"
#include "graphicselement.h"

GameLayerResources::GameLayerResources(Gorilla::Silverback& silverback, Ogre::Viewport& viewport)
{
    mScreen = silverback.createScreen(&viewport, "tripleflip");
    mScreen->setOrientation(Ogre::OR_PORTRAIT);
    
    mCoinHeadSprite = mScreen->getAtlas()->getSprite("coinhead");
    mCoinTailSprite = mScreen->getAtlas()->getSprite("cointail");
    
    mLoseSprite = Screen().getAtlas()->getSprite("lose"); 
    mWinSprite = Screen().getAtlas()->getSprite("win"); 
    mBigWinSprite = Screen().getAtlas()->getSprite("bigwin"); 
    
    mDoubleupSprite = Screen().getAtlas()->getSprite("doubleup");
}

GameLayerResources::~GameLayerResources()
{
    delete mDoubleupSprite;
    delete mBigWinSprite;
    delete mWinSprite;
    delete mLoseSprite;
    delete mCoinTailSprite;
    delete mCoinHeadSprite;
}

Gorilla::Layer* GameLayerResources::CreateLayer(int order)
{
    return mScreen->createLayer(order);
}

GraphicsElement* GameLayerResources::createGraphicsElement(Gorilla::Layer& layer, std::string name, int x, int y)
{
    return new GraphicsElement(*mScreen, layer, name, x, y);
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

Gorilla::Sprite& GameLayerResources::BigwinText()
{
    return *mBigWinSprite;
}

Gorilla::Sprite& GameLayerResources::WinText()
{
    return *mWinSprite;
}

Gorilla::Sprite& GameLayerResources::LoseText()
{
    return *mLoseSprite;
}

Gorilla::Sprite& GameLayerResources::DoubleupText()
{
    return *mDoubleupSprite;
}
