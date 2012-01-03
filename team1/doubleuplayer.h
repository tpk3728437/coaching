#ifndef DOUBLEUPLAYER_H
#define DOUBLEUPLAYER_H

#include "Gorilla.h"
#include "globals.h"


class DoubleupLayer
{
public:
    DoubleupLayer(Gorilla::Silverback& silverback, Ogre::Viewport& viewport);
    ~DoubleupLayer();
    
    void show();
    void hide();

private:

private:
    Gorilla::Screen*        mScreen;
    Gorilla::Layer*         mLayer;

};

#endif // DOUBLEUPLAYER_H
