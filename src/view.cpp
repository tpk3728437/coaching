#include "view.h"
#include "graphics.h"
#include "backgroundlayer.h"
#include "gamelayer.h"
#include "doubleuplayer.h"
#include "layerfactory.h"

View::View()
{
    mGraphics = new Graphics();

    mBackgroundLayer = new BackgroundLayer(mGraphics->getSilverback(), mGraphics->getViewport());
    mLayerFactory = new LayerFactory(mGraphics->getSilverback(), mGraphics->getViewport());
    mGameLayer = new GameLayer(*mLayerFactory);
    mDoubleupLayer = new DoubleupLayer(*mLayerFactory);
}

View::~View()
{
    delete mDoubleupLayer;
    delete mGameLayer;
    delete mBackgroundLayer;
    delete mGraphics;
}

void View::startRendering()
{
    mGraphics->startRendering();
}

void View::quit()
{
    mGraphics->quit();
}

void View::showDoubleupResult(bool win)
{
    mDoubleupLayer->show();
    mDoubleupLayer->result(win);
}

void View::resetDoubleUpScreenGraphics()
{
    mDoubleupLayer->resetGraphics();
}

void View::showGameLoss()
{
    if (!mDoubleupLayer->isVisible())
    {
        mGameLayer->showLoss();
    }
}

void View::showDoubleUpScreen()
{
    mGameLayer->showDoubleupQueryBoxes();
}

void View::showBigWin()
{
    mGameLayer->showBigWin();
}

void View::showBaseGameCoin(int index, Side side)
{
    mGameLayer->setCoinImage(index, side);
}

void View::showDoubleUpCoin(Side side)
{
    mDoubleupLayer->setCoin(side);
}

void View::setInputInspector(InputInspector& inputInspector)
{
    mGraphics->setInputInspector(inputInspector);
}

void View::resetGraphics()
{
    mDoubleupLayer->hide();
    mGameLayer->resetGraphics();
}

ViewportSize View::getViewportSize() const
{
    return mGraphics->getViewportSize();
}

std::string View::windowHandle() const
{
    return mGraphics->windowHandle();
}
