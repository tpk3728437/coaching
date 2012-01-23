#include "doubleuplayer.h"
#include "gamelayerresources.h"


DoubleupLayer::DoubleupLayer(GameLayerResources& resources) :
    mResources(resources)
{
    mLayer = resources.Screen().createLayer(2);
    mLayer->setAlphaModifier(0.95);
    Gorilla::Rectangle* dimmingRect = mLayer->createRectangle(0, 0, 1024, 768);
    dimmingRect->background_gradient(Gorilla::Gradient_Diagonal, Gorilla::rgb(128,128,128), Gorilla::rgb(130,126,120));

    const Ogre::Real coinTopLeftx = resources.Screen().getWidth()/2 - resources.CoinHead().spriteWidth/2;
    const Ogre::Real coinTopLefty = resources.Screen().getHeight()/2 - resources.CoinHead().spriteHeight/2;

    mCoinRect = mLayer->createRectangle(coinTopLeftx, coinTopLefty, resources.CoinHead().spriteWidth, resources.CoinHead().spriteHeight);
    mCoinRect->background_image("opaque");

    Ogre::Real vpHeight = mResources.Screen().getHeight();
    mResultRect = mLayer->createRectangle(100,vpHeight-400, mResources.LoseText().spriteWidth, mResources.LoseText().spriteHeight);
    mResultRect->background_image("opaque");

    mLayer->hide();
}

DoubleupLayer::~DoubleupLayer()
{
}

void DoubleupLayer::ResetGraphics()
{
    mCoinRect->background_image("opaque");
    mResultRect->background_image("opaque");
}

void DoubleupLayer::SetCoin(Side side)
{
    if (side == Heads)
    {
        mCoinRect->background_image(&mResources.CoinHead());
    }
    else
    {
        mCoinRect->background_image(&mResources.CoinTail());
    }
}

bool DoubleupLayer::IsVisible()
{
    mLayer->isVisible();
}

void DoubleupLayer::Result(bool win)
{
    if (win)
    {
        mResultRect->background_image(&mResources.WinText());
    }
    else
    {
        mResultRect->background_image(&mResources.LoseText());
    }
}

void DoubleupLayer::Show()
{
    mLayer->show();
}

void DoubleupLayer::Hide()
{
    ResetGraphics();
    mLayer->hide();
}
