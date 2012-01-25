#ifndef LAYERFACTORY_H
#define LAYERFACTORY_H

#include "gorilla.h"

class GraphicsElement;

class LayerFactory
{
public:
    LayerFactory(Gorilla::Silverback& silverback, Ogre::Viewport& viewport);
    ~LayerFactory();
    
    Gorilla::Layer* CreateLayer(int order);
    GraphicsElement* createGraphicsElement(Gorilla::Layer& layer, std::string name, int x, int y);
    GraphicsElement* createGraphicsElement(Gorilla::Layer& layer, std::vector<std::string> names, int x, int y);
    
    int ScreenWidth() const;
    int ScreenHeight() const;

private:
    Gorilla::Screen*        mScreen;
};

#endif // LAYERFACTORY_H
