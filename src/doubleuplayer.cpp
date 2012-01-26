#include "doubleuplayer.h"
#include "layerfactory.h"
#include "graphicselement.h"


DoubleupLayer::DoubleupLayer(LayerFactory& factory)
{
    mLayer = factory.createLayer(2);
    mLayer->setAlphaModifier(0.9);
    Gorilla::Rectangle* dimmingRect = mLayer->createRectangle(0, 0, 1024, 768);
    dimmingRect->background_gradient(Gorilla::Gradient_Diagonal, Gorilla::rgb(128,128,128), Gorilla::rgb(130,126,120));

    createCoins(factory);
    createResultElements(factory);
    createDoubleupBox(factory);

    mLayer->hide();
}

DoubleupLayer::~DoubleupLayer()
{
    delete mDoubleUp;
    delete mCoin;
}

void DoubleupLayer::resetGraphics()
{
    mDoubleUp->setVisibility(false);
    mCoin->setVisibility(false);
    mResult->setVisibility(false);
}

void DoubleupLayer::setCoin(Side side)
{
    if (side == Heads)
    {
        mCoin->show("coinhead");
    }
    else
    {
        mCoin->show("cointail");
    }
}

bool DoubleupLayer::isVisible()
{
    mLayer->isVisible();
}

void DoubleupLayer::result(bool win)
{
    if (win)
    {
        mResult->show("win");
        showDoubleUpQuery();
    }
    else
    {
        mResult->show("lose");
    }
}

void DoubleupLayer::show()
{
    mLayer->show();
}

void DoubleupLayer::showDoubleUpQuery()
{
    mDoubleUp->setVisibility(true);
}

void DoubleupLayer::hide()
{
    resetGraphics();
    mLayer->hide();
}

void DoubleupLayer::createCoins(LayerFactory& factory)
{
    const Ogre::Real coinX = factory.screenWidth()/2 - 50;
    const Ogre::Real coinY = factory.screenHeight()/2 - 100;

    std::vector<std::string> names;
    names.push_back("coinhead");
    names.push_back("cointail");
    mCoin = factory.createGraphicsElement(*mLayer, names, coinX, coinY);
    mCoin->setVisibility(false);
}

void DoubleupLayer::createResultElements(LayerFactory& factory)
{
    std::vector<std::string> names;
    names.push_back("win");
    names.push_back("lose");
 
    Ogre::Real vpHeight = factory.screenHeight();
    mResult = factory.createGraphicsElement(*mLayer, names, 100, vpHeight-400);
    mResult->setVisibility(false);
}

void DoubleupLayer::createDoubleupBox(LayerFactory& factory)
{
    Ogre::Real vpHeight = factory.screenHeight();
    mDoubleUp = factory.createGraphicsElement(*mLayer, "doubleup", 300, vpHeight-200);
    mDoubleUp->setVisibility(false);
}
