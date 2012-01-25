#include "doubleuplayer.h"
#include "layerfactory.h"
#include "graphicselement.h"


DoubleupLayer::DoubleupLayer(LayerFactory& factory)
{
    mLayer = factory.CreateLayer(2);
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

void DoubleupLayer::ResetGraphics()
{
    mDoubleUp->SetVisibility(false);
    mCoin->SetVisibility(false);
    mResult->SetVisibility(false);
}

void DoubleupLayer::SetCoin(Side side)
{
    if (side == Heads)
    {
        mCoin->Show("coinhead");
    }
    else
    {
        mCoin->Show("cointail");
    }
}

bool DoubleupLayer::IsVisible()
{
    mLayer->isVisible();
}

void DoubleupLayer::Result(bool win)
{
    if (win)
    {
        mResult->Show("win");
        ShowDoubleUpQuery();
    }
    else
    {
        mResult->Show("lose");
    }
}

void DoubleupLayer::Show()
{
    mLayer->show();
}

void DoubleupLayer::ShowDoubleUpQuery()
{
    mDoubleUp->SetVisibility(true);
}

void DoubleupLayer::Hide()
{
    ResetGraphics();
    mLayer->hide();
}

void DoubleupLayer::createCoins(LayerFactory& factory)
{
    const Ogre::Real coinX = factory.ScreenWidth()/2 - 50;
    const Ogre::Real coinY = factory.ScreenHeight()/2 - 100;

    std::vector<std::string> names;
    names.push_back("coinhead");
    names.push_back("cointail");
    mCoin = factory.createGraphicsElement(*mLayer, names, coinX, coinY);
    mCoin->SetVisibility(false);
}

void DoubleupLayer::createResultElements(LayerFactory& factory)
{
    std::vector<std::string> names;
    names.push_back("win");
    names.push_back("lose");
 
    Ogre::Real vpHeight = factory.ScreenHeight();
    mResult = factory.createGraphicsElement(*mLayer, names, 100, vpHeight-400);
    mResult->SetVisibility(false);
}

void DoubleupLayer::createDoubleupBox(LayerFactory& factory)
{
    Ogre::Real vpHeight = factory.ScreenHeight();
    mDoubleUp = factory.createGraphicsElement(*mLayer, "doubleup", 300, vpHeight-200);
    mDoubleUp->SetVisibility(false);
}
