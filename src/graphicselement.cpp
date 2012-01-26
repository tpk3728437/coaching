#include "graphicselement.h"

typedef std::pair<std::string, Gorilla::Sprite*> ElementPair;

namespace {
    bool widthCompare(const ElementPair& lhs, const ElementPair& rhs) 
    { 
        return lhs.second->spriteWidth < rhs.second->spriteWidth; 
    }

    bool heightCompare(const ElementPair& lhs, const ElementPair& rhs) 
    { 
        return lhs.second->spriteHeight < rhs.second->spriteHeight; 
    }

    struct NameComparator
    {
        NameComparator(std::string name) : mName(name) {}
        bool operator()(const ElementPair& elem) const { return mName.compare(elem.first) == 0; }
    private:
        std::string mName;
    };
};


GraphicsElement::GraphicsElement(Gorilla::Screen& screen, Gorilla::Layer& layer, std::string name, int x, int y) : 
        mRectangle(0), mActiveImageName(name)
{
    Gorilla::Sprite* sprite = screen.getAtlas()->getSprite(name); 
    mSpriteMap.insert(ElementPair(name, sprite));
    mRectangle = layer.createRectangle(x, y, sprite->spriteWidth, sprite->spriteHeight);
    mRectangle->background_image(sprite);
}

GraphicsElement::GraphicsElement(Gorilla::Screen& screen, Gorilla::Layer& layer, std::vector<std::string>& names, int x, int y) : 
        mRectangle(0), mActiveImageName(names[0])
{
    for (std::vector<std::string>::iterator i = names.begin(); i != names.end(); ++i)
    {
        const std::string spriteName = *i;
        Gorilla::Sprite* sprite = screen.getAtlas()->getSprite(spriteName);         
        mSpriteMap.insert(ElementPair(spriteName, sprite));
    }
    mRectangle = layer.createRectangle(x, y, maxSpriteWidth(), maxSpriteHeight());
    Gorilla::Sprite* sprite = find(mActiveImageName);
    mRectangle->background_image(sprite);
}

GraphicsElement::~GraphicsElement()
{
    for(ElementMap::iterator it = mSpriteMap.begin(); it != mSpriteMap.end(); ++it)
    {
        delete (*it).second;
    }
}

void GraphicsElement::setVisibility(bool isVisible)
{
    if (isVisible)
    {
        Gorilla::Sprite* sprite = find(mActiveImageName);
        assert(sprite);
        mRectangle->background_image(sprite);
    }
    else
    {
        mRectangle->background_image("opaque");
    }
}

void GraphicsElement::show(std::string name)
{
    Gorilla::Sprite* sprite = find(name);
    assert(sprite);
    if (sprite)
    {
        mActiveImageName = name; 
        mRectangle->background_image(sprite);
    }
}

int GraphicsElement::maxSpriteWidth() const
{
    ElementMap::const_iterator it = std::max_element(mSpriteMap.begin(), mSpriteMap.end(), widthCompare);
    return (*it).second->spriteWidth;
}

int GraphicsElement::maxSpriteHeight() const
{
    ElementMap::const_iterator it = std::max_element(mSpriteMap.begin(), mSpriteMap.end(), heightCompare);
    return (*it).second->spriteHeight;
}

Gorilla::Sprite* GraphicsElement::find(std::string name) const
{
    NameComparator pred(name);
    ElementMap::const_iterator iter = std::find_if(mSpriteMap.begin(), mSpriteMap.end(), pred);
    Gorilla::Sprite* sprite = (*iter).second;
    assert(sprite);
    return sprite;
}
