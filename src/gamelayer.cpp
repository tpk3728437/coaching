#include "gamelayer.h"
#include "layerfactory.h"
#include "graphicselement.h"

GameLayer::GameLayer(LayerFactory& factory)
{
    mLayer = factory.createLayer(1);
    mLogo = factory.createGraphicsElement(*mLayer, "logo", 100, 0);   

    createCoinRectangles(factory);
    createWinLogos(factory);
    createDoubleupBox(factory);
}

GameLayer::~GameLayer()
{
    delete mDoubleUp;
    delete mResult;
    for (GraphicsElementVector::iterator it = mCoins.begin(); it != mCoins.end(); ++it)
    {
        delete *it;
    }
    delete mLogo;
}

void GameLayer::resetGraphics()
{
    for(GraphicsElementVector::iterator i = mCoins.begin(); i != mCoins.end(); ++i)
    {
        (*i)->setVisibility(false);
    }
    mResult->setVisibility(false);
    mDoubleUp->setVisibility(false);
}

void GameLayer::setCoinImage(int index, Side side)
{
    if (side == Heads) 
    {
        mCoins[index]->show("coinhead");
    }
    else 
    {
        mCoins[index]->show("cointail");
    }
}

void GameLayer::showBigWin()
{
    mResult->show("bigwin");
}

void GameLayer::showLoss()
{
    mResult->show("lose");
}

void GameLayer::showDoubleupQueryBoxes()
{
    mDoubleUp->setVisibility(true);
}

void GameLayer::createCoinRectangles(LayerFactory& factory)
{
    std::vector<std::string> names;
    names.push_back("coinhead");
    names.push_back("cointail");
    for (int i = 0; i <= 2; ++i)
    {
        const int xPos = 100 + i * 300;
        GraphicsElement* coin = factory.createGraphicsElement(*mLayer, names, xPos, 300);
        coin->setVisibility(false);
        mCoins.push_back(coin);
    }    
}

void GameLayer::createWinLogos(LayerFactory& factory)
{
    std::vector<std::string> names;
    names.push_back("bigwin");
    names.push_back("lose");
    names.push_back("win");
    const Ogre::Real yPos = factory.screenHeight() - 200;
    mResult = factory.createGraphicsElement(*mLayer, names, 100, yPos);
    mResult->setVisibility(false);
}

void GameLayer::createDoubleupBox(LayerFactory& factory)
{
    const Ogre::Real yPos = factory.screenHeight() - 200;
    mDoubleUp = factory.createGraphicsElement(*mLayer, "doubleup", 300, yPos);
    mDoubleUp->setVisibility(false);
}
