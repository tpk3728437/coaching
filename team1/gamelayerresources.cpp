#include "gamelayerresources.h"

GameLayerResources::GameLayerResources(Gorilla::Silverback& silverback, Ogre::Viewport& viewport)
{
    silverback.loadAtlas("tripleflip");

    mScreen = silverback.createScreen(&viewport, "tripleflip");
    mScreen->setOrientation(Ogre::OR_PORTRAIT);
    
    mCoinHeadSprite = mScreen->getAtlas()->getSprite("coinhead");
    mCoinTailSprite = mScreen->getAtlas()->getSprite("cointail");
    
    mLoseSprite = Screen().getAtlas()->getSprite("lose"); 
    mWinSprite = Screen().getAtlas()->getSprite("win"); 
    mBigWinSprite = Screen().getAtlas()->getSprite("bigwin"); 
    
    mYesBoxSprite = Screen().getAtlas()->getSprite("yesbox");
    mNoBoxSprite = Screen().getAtlas()->getSprite("nobox");
}

GameLayerResources::~GameLayerResources()
{
    delete mNoBoxSprite;
    delete mYesBoxSprite;
    delete mBigWinSprite;
    delete mWinSprite;
    delete mLoseSprite;
    delete mCoinTailSprite;
    delete mCoinHeadSprite;
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

Gorilla::Sprite& GameLayerResources::YesBox()
{
    return *mYesBoxSprite;
}

Gorilla::Sprite& GameLayerResources::NoBox()
{
    return *mNoBoxSprite;
}
