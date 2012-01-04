#include "doubleuplayer.h"
#include "gamelayerresources.h"


DoubleupLayer::DoubleupLayer(Gorilla::Silverback& silverback, Ogre::Viewport& viewport, GameLayerResources& resources) :
    mResources(resources)
{
    mLayer = resources.Screen().createLayer(2);
    mLayer->setAlphaModifier(0.7);
    Gorilla::Rectangle* dimmingRect = mLayer->createRectangle(100, 150, 800, 500);
    dimmingRect->background_gradient(Gorilla::Gradient_Diagonal, Gorilla::rgb(98,0,63), Gorilla::rgb(255,180,174));

    mLayer->hide();
}

DoubleupLayer::~DoubleupLayer()
{
}

void DoubleupLayer::SetCoin(Side side)
{
    std::cout << "Double up Side:" << side << std::endl;
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
