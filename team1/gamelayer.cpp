#include "gamelayer.h"

GameLayer::GameLayer(Gorilla::Silverback& silverback, Ogre::Viewport& viewport)
{
    silverback.loadAtlas("tripleflip");

    mScreen = silverback.createScreen(&viewport, "tripleflip");
    mScreen->setOrientation(Ogre::OR_PORTRAIT);
    Ogre::Real vpWidth = mScreen->getWidth(); 
    Ogre::Real vpHeight = mScreen->getHeight();

    mLayer = mScreen->createLayer(1);    
    Gorilla::Sprite* logoSprite = mScreen->getAtlas()->getSprite("logo"); 
    Gorilla::Rectangle* logoRect = mLayer->createRectangle(100,0, logoSprite->spriteWidth, logoSprite->spriteHeight);
    logoRect->background_image(logoSprite);

    createCoinSprites();
    createWinLogos();
}

GameLayer::~GameLayer()
{
}

void GameLayer::ResetGraphics()
{
    for (RectangleVector::iterator i = mCoinRectangles.begin(); i != mCoinRectangles.end(); ++i)
    {
        (*i)->background_image("opaque");
    }
    mResultRect->background_image("opaque");
}

void GameLayer::setCoinImage(int index, Side side)
{
    if (side == Heads) 
    {
        std::cout << "coin rect addr:" << mCoinRectangles[index] << std::endl;
        mCoinRectangles[index]->background_image(mCoinHeadSprite);
    }
    else 
    {
        mCoinRectangles[index]->background_image(mCoinTailSprite);
    }
}

void GameLayer::showBigWin()
{
    mResultRect->background_image(mBigwinSprite);
}

void GameLayer::showWin()
{
    mResultRect->background_image(mWinSprite);
}

void GameLayer::showLoss()
{
    mResultRect->background_image(mLoseSprite);
}


void GameLayer::createCoinSprites()
{
    mCoinHeadSprite = mScreen->getAtlas()->getSprite("coinhead");
    mCoinTailSprite = mScreen->getAtlas()->getSprite("cointail");
    
    for (int i = 0; i <= 2; ++i)
    {
        const int horizontalPosition = 100 + i * 300;
        const Ogre::Vector2 coinSize(mCoinHeadSprite->spriteWidth, mCoinHeadSprite->spriteHeight);    
        
        Gorilla::Rectangle* coinRect = mLayer->createRectangle(Ogre::Vector2(horizontalPosition,300), coinSize);
        coinRect->background_image("opaque");
        mCoinRectangles.push_back(coinRect);
    }
}

void GameLayer::createWinLogos()
{
    mLoseSprite = mScreen->getAtlas()->getSprite("lose"); 
    mWinSprite = mScreen->getAtlas()->getSprite("win"); 
    mBigwinSprite = mScreen->getAtlas()->getSprite("bigwin"); 

    Ogre::Real vpHeight = mScreen->getHeight();
    mResultRect = mLayer->createRectangle(100,vpHeight-200, mBigwinSprite->spriteWidth, mWinSprite->spriteHeight);
    mResultRect->background_image("opaque");
}
