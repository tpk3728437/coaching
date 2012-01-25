#ifndef GRAPHICSELEMENT_H
#define GRAPHICSELEMENT_H

#include "gorilla.h"

class GraphicsElement
{
public:
    GraphicsElement(Gorilla::Screen& screen, Gorilla::Layer& layer, std::string name, int x, int y);
    virtual ~GraphicsElement();
    
    virtual void SetVisibility(bool isVisible);
    
private:
    Gorilla::Sprite* mSprite;
    Gorilla::Rectangle* mRectangle;
};

#endif // GRAPHICSELEMENT_H
