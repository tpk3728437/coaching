#include "gamelayer.h"
#include "gamelayerresources.h"

GameLayer::GameLayer(Gorilla::Silverback& silverback, Ogre::Viewport& viewport, GameLayerResources& resources) :
    mResources(resources)
{
    mLayer = Screen().createLayer(1);    
    Gorilla::Sprite* logoSprite = Screen().getAtlas()->getSprite("logo"); 
    Gorilla::Rectangle* logoRect = mLayer->createRectangle(100,0, logoSprite->spriteWidth, logoSprite->spriteHeight);
    logoRect->background_image(logoSprite);

    createCoinRectangles();
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
        mCoinRectangles[index]->background_image(&mResources.CoinHead());
    }
    else 
    {
        mCoinRectangles[index]->background_image(&mResources.CoinTail());
    }
}

void GameLayer::showBigWin()
{
    mResultRect->background_image(mBigwinSprite);
}

void GameLayer::showWin()
{
    mResultRect->background_image(&mResources.WinText());
}

void GameLayer::showLoss()
{
    mResultRect->background_image(&mResources.LoseText());
}

void GameLayer::createCoinRectangles()
{
    Gorilla::Sprite& headSprite = mResources.CoinHead();
    
    for (int i = 0; i <= 2; ++i)
    {
        const int horizontalPosition = 100 + i * 300;
        const Ogre::Vector2 coinSize(headSprite.spriteWidth, headSprite.spriteHeight);    
        
        Gorilla::Rectangle* coinRect = mLayer->createRectangle(Ogre::Vector2(horizontalPosition,300), coinSize);
        coinRect->background_image("opaque");
        mCoinRectangles.push_back(coinRect);
    }
}

void GameLayer::createWinLogos()
{
    mBigwinSprite = Screen().getAtlas()->getSprite("bigwin"); 

    Ogre::Real vpHeight = Screen().getHeight();
    mResultRect = mLayer->createRectangle(100,vpHeight-200, mBigwinSprite->spriteWidth, mResources.LoseText().spriteHeight);
    mResultRect->background_image("opaque");
}

Gorilla::Screen& GameLayer::Screen()
{
    return mResources.Screen();
}
