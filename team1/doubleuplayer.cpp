#include "doubleuplayer.h"
#include "gamelayerresources.h"


DoubleupLayer::DoubleupLayer(Gorilla::Silverback& silverback, Ogre::Viewport& viewport, GameLayerResources& resources) :
    mResources(resources)
{
    mLayer = resources.Screen().createLayer(2);
    mLayer->setAlphaModifier(0.9);
    Gorilla::Rectangle* dimmingRect = mLayer->createRectangle(100, 150, 800, 500);
    dimmingRect->background_gradient(Gorilla::Gradient_Diagonal, Gorilla::rgb(140,52, 21), Gorilla::rgb(156,39,3));

    const Ogre::Real coinTopLeftx = resources.Screen().getWidth()/2 - resources.CoinHead().spriteWidth/2;
    const Ogre::Real coinTopLefty = resources.Screen().getHeight()/2 - resources.CoinHead().spriteHeight/2;

    mCoinRect = mLayer->createRectangle(coinTopLeftx, coinTopLefty, resources.CoinHead().spriteWidth, resources.CoinHead().spriteHeight);
    mCoinRect->background_image("opaque");

    mLayer->hide();
}

DoubleupLayer::~DoubleupLayer()
{
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

void DoubleupLayer::Show()
{
    mLayer->show();
    
    // arpoo kolikko ja näyttää se
}

void DoubleupLayer::Hide()
{
    mLayer->hide();
}
