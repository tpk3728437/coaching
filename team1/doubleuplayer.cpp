#include "doubleuplayer.h"

DoubleupLayer::DoubleupLayer(Gorilla::Silverback& silverback, Ogre::Viewport& viewport)
{
    mScreen = silverback.createScreen(&viewport, "tripleflip");
    mScreen->setOrientation(Ogre::OR_PORTRAIT);
    Ogre::Real vpWidth = mScreen->getWidth(); 
    Ogre::Real vpHeight = mScreen->getHeight();

    mLayer = mScreen->createLayer(2);
    mLayer->setAlphaModifier(0.7);
    Gorilla::Rectangle* dimmingRect = mLayer->createRectangle(100, 150, 800, 500);
    dimmingRect->background_gradient(Gorilla::Gradient_Diagonal, Gorilla::rgb(98,0,63), Gorilla::rgb(255,180,174));

    mLayer->hide();
}

DoubleupLayer::~DoubleupLayer()
{
}

void DoubleupLayer::show()
{
    mLayer->show();
    
    // arpoo kolikko ja näyttää se
}

void DoubleupLayer::hide()
{
    mLayer->hide();
}
