#include "backgroundlayer.h"

BackgroundLayer::BackgroundLayer(Gorilla::Silverback& silverback, Ogre::Viewport& viewport) :
    mSilverback(silverback)
{
    mBackgroundScreen = silverback.createScreen(&viewport, "background");
    mBackgroundScreen->setOrientation(Ogre::OR_PORTRAIT);
    Ogre::Real vpWidth = mBackgroundScreen->getWidth(); 
    Ogre::Real vpHeight = mBackgroundScreen->getHeight();

    mBackgroundLayer = mBackgroundScreen->createLayer(0);
    Gorilla::Rectangle* backgroundRect = mBackgroundLayer->createRectangle(0,0, vpWidth, vpHeight);
    backgroundRect->background_image("background");
}

BackgroundLayer::~BackgroundLayer()
{
}
