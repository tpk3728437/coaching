#include "layerfactory.h"
#include "graphicselement.h"

    
LayerFactory::LayerFactory(Gorilla::Silverback& silverback, Ogre::Viewport& viewport)
{
    mScreen = silverback.createScreen(&viewport, "tripleflip");
    mScreen->setOrientation(Ogre::OR_PORTRAIT);
}

LayerFactory::~LayerFactory()
{
}

Gorilla::Layer* LayerFactory::createLayer(int order)
{
    return mScreen->createLayer(order);
}

GraphicsElement* LayerFactory::createGraphicsElement(Gorilla::Layer& layer, std::string name, int x, int y)
{
    return new GraphicsElement(*mScreen, layer, name, x, y);
}

GraphicsElement* LayerFactory::createGraphicsElement(Gorilla::Layer& layer, std::vector<std::string> names, int x, int y)
{
    return new GraphicsElement(*mScreen, layer, names, x, y);
}

int LayerFactory::screenWidth() const
{
    return mScreen->getWidth();
}

int LayerFactory::screenHeight() const
{
    return mScreen->getHeight();
}
