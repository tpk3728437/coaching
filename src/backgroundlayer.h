#ifndef BACKGROUNDLAYER_H
#define BACKGROUNDLAYER_H

#include "Gorilla.h"


class BackgroundLayer
{
public:    
    BackgroundLayer(Gorilla::Silverback& silverback, Ogre::Viewport& viewport);
    ~BackgroundLayer();
    
private:

private:
    Gorilla::Silverback&    mSilverback;
    Gorilla::Screen*        mBackgroundScreen;
    Gorilla::Layer*         mBackgroundLayer;
};

#endif // BACKGROUNDLAYER_H
