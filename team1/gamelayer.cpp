#include "gamelayer.h"
#include "gamelayerresources.h"

GameLayer::GameLayer(GameLayerResources& resources) :
    mResources(resources)
{
    mLayer = Screen().createLayer(1);    
    mLogoSprite = Screen().getAtlas()->getSprite("logo"); 
    Gorilla::Rectangle* logoRect = mLayer->createRectangle(100,0, mLogoSprite->spriteWidth, mLogoSprite->spriteHeight);
    logoRect->background_image(mLogoSprite);

    createCoinRectangles();
    createWinLogos();
    createDoubleupBoxes();
}

GameLayer::~GameLayer()
{
    delete mLogoSprite;
}

void GameLayer::ResetGraphics()
{
    for (RectangleVector::iterator i = mCoinRectangles.begin(); i != mCoinRectangles.end(); ++i)
    {
        (*i)->background_image("opaque");
    }
    mResultRect->background_image("opaque");
    mYesBoxRect->background_image("opaque");
    mNoBoxRect->background_image("opaque");
}

void GameLayer::setCoinImage(int index, Side side)
{
    if (side == Heads) 
    {
        mCoinRectangles[index]->background_image(&mResources.CoinHead());
    }
    else 
    {
        mCoinRectangles[index]->background_image(&mResources.CoinTail());
    }
}

void GameLayer::showBigWin()
{
    mResultRect->background_image(&mResources.BigwinText());
}

void GameLayer::showWin()
{
    mResultRect->background_image(&mResources.WinText());
}

void GameLayer::showLoss()
{
    mResultRect->background_image(&mResources.LoseText());
}

void GameLayer::showDoubleupQueryBoxes()
{
    mYesBoxRect->background_image(&mResources.YesBox());
    mNoBoxRect->background_image(&mResources.NoBox());
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
    Ogre::Real vpHeight = Screen().getHeight();
    mResultRect = mLayer->createRectangle(100,vpHeight-200, mResources.BigwinText().spriteWidth, mResources.LoseText().spriteHeight);
    mResultRect->background_image("opaque");
}

void GameLayer::createDoubleupBoxes()
{
    Ogre::Real vpHeight = Screen().getHeight();
    mYesBoxRect = mLayer->createRectangle(300,vpHeight-200, mResources.YesBox().spriteWidth, mResources.YesBox().spriteHeight);
    mYesBoxRect->background_image("opaque");

    mNoBoxRect = mLayer->createRectangle(500,vpHeight-200, mResources.NoBox().spriteWidth, mResources.NoBox().spriteHeight);
    mNoBoxRect->background_image("opaque");
}

Gorilla::Screen& GameLayer::Screen()
{
    return mResources.Screen();
}
