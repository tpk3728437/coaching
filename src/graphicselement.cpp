#include "graphicselement.h"

GraphicsElement::GraphicsElement(Gorilla::Screen& screen, Gorilla::Layer& layer, std::string name, int x, int y) : 
        mRectangle(0), mActiveImageName(name)
{
    Gorilla::Sprite* sprite = screen.getAtlas()->getSprite(name); 
    mSpriteMap.insert(std::pair<std::string, Gorilla::Sprite*>(name, sprite));
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
        mSpriteMap.insert(std::pair<std::string, Gorilla::Sprite*>(spriteName, sprite));
    }
    mRectangle = layer.createRectangle(x, y, maxSpriteWidth(), maxSpriteHeight());
    Gorilla::Sprite* sprite = find(mActiveImageName);
    mRectangle->background_image(sprite);
}

GraphicsElement::~GraphicsElement()
{
    for(std::map<std::string, Gorilla::Sprite*>::iterator it = mSpriteMap.begin(); it != mSpriteMap.end(); ++it)
    {
        delete (*it).second;
    }
}

void GraphicsElement::SetVisibility(bool isVisible)
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

void GraphicsElement::Show(std::string name)
{
    Gorilla::Sprite* sprite = find(name);
    assert(sprite);
    if (sprite)
    {
        mActiveImageName = name; 
        mRectangle->background_image(sprite);
    }
}

struct MaxWidthFinder
{
    MaxWidthFinder(int& width) : max(width) {}
    void operator()(const std::pair<std::string, Gorilla::Sprite*>& elem) { if (elem.second->spriteWidth > max) { max = elem.second->spriteWidth; } }
private:
    int& max;
};

struct MaxHeightFinder
{
    MaxHeightFinder(int& height) : max(height) {}
    void operator()(const std::pair<std::string, Gorilla::Sprite*>& elem) { if (elem.second->spriteHeight > max) { max = elem.second->spriteHeight; } }
private:
    int& max;
};


int GraphicsElement::maxSpriteWidth() const
{
    int width = 0;
    std::for_each(mSpriteMap.begin(), mSpriteMap.end(), MaxWidthFinder(width));
    return width;
}

int GraphicsElement::maxSpriteHeight() const
{
    int height = 0;
    std::for_each(mSpriteMap.begin(), mSpriteMap.end(), MaxHeightFinder(height));
    return height;
}

struct NameComparator
{
    NameComparator(std::string name) : mName(name) {}
    bool operator()(const std::pair<std::string, Gorilla::Sprite*>& elem) const { return mName.compare(elem.first) == 0; }
private:
    std::string mName;
};

Gorilla::Sprite* GraphicsElement::find(std::string name) const
{
    NameComparator pred(name);
    std::map<std::string, Gorilla::Sprite*>::const_iterator iter = std::find_if(mSpriteMap.begin(), mSpriteMap.end(), pred);
    Gorilla::Sprite* sprite = (*iter).second;
    assert(sprite);
    return sprite;
}
