#ifndef GRAPHICSELEMENT_H
#define GRAPHICSELEMENT_H

#include "gorilla.h"

class GraphicsElement
{
public:
    GraphicsElement(Gorilla::Screen& screen, Gorilla::Layer& layer, std::string name, int x, int y);
    GraphicsElement(Gorilla::Screen& screen, Gorilla::Layer& layer, std::vector<std::string>& names, int x, int y);
    virtual ~GraphicsElement();
    
    void setVisibility(bool isVisible);
    void show(std::string name);
    
protected:
    int maxSpriteWidth() const; 
    int maxSpriteHeight() const;
    Gorilla::Sprite* find(std::string name) const;
    
private:
    typedef std::map<std::string, Gorilla::Sprite*> ElementMap;
    ElementMap mSpriteMap;
    Gorilla::Rectangle* mRectangle;
    std::string mActiveImageName;
};

#endif // GRAPHICSELEMENT_H
