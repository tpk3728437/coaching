#include "graphicselement.h"

GraphicsElement::GraphicsElement(Gorilla::Screen& screen, Gorilla::Layer& layer, std::string name, int x, int y) : 
        mSprite(0), mRectangle(0)
{
    mSprite = screen.getAtlas()->getSprite(name); 
    mRectangle = layer.createRectangle(x, y, mSprite->spriteWidth, mSprite->spriteHeight);
    mRectangle->background_image(mSprite);
}

GraphicsElement::~GraphicsElement()
{
//    TODO: delete objects 
}

void GraphicsElement::SetVisibility(bool isVisible)
{
    if (isVisible)
    {
        mRectangle->background_image(mSprite);
    }
    else
    {
        mRectangle->background_image("opaque");
    }
}
