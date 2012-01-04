#ifndef DOUBLEUPLAYER_H
#define DOUBLEUPLAYER_H

#include "Gorilla.h"
#include "globals.h"

class GameLayerResources;

class DoubleupLayer
{
public:
    DoubleupLayer(Gorilla::Silverback& silverback, Ogre::Viewport& viewport, GameLayerResources& resources);
    ~DoubleupLayer();
    void SetCoin(Side side);
    
    void Show();
    void Hide();

private:

private:
    Gorilla::Layer*         mLayer;
    GameLayerResources&     mResources;
};

#endif // DOUBLEUPLAYER_H
