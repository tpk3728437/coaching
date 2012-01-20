#include "view.h"
#include "graphics.h"
#include "backgroundlayer.h"
#include "gamelayer.h"
#include "doubleuplayer.h"
#include "gamelayerresources.h"

View::View()
{
    initializeGraphics();
    createLayers();
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

void View::Quit()
{
    mGraphics->Quit();
}

void View::ShowDoubleupResult(bool win)
{
    mDoubleupLayer->Show();
    mDoubleupLayer->Result(win);
}

void View::ResetDoubleUpScreenGraphics()
{
    mDoubleupLayer->ResetGraphics();
}

void View::ShowGameLoss()
{
    if (!mDoubleupLayer->IsVisible())
    {
        mGameLayer->showLoss();
    }
}

void View::ShowDoubleUpScreen()
{
    mGameLayer->showDoubleupQueryBoxes();
}

void View::ShowBigWin()
{
    mGameLayer->showBigWin();
}

void View::ShowBaseGameCoin(int index, Side side)
{
    mGameLayer->setCoinImage(index, side);
}

void View::ShowDoubleUpCoin(Side side)
{
    mDoubleupLayer->SetCoin(side);
}

void View::setInputInspector(InputInspector& inputInspector)
{
    mGraphics->setInputInspector(inputInspector);
}

void View::ResetGraphics()
{
    mDoubleupLayer->Hide();
    mGameLayer->ResetGraphics();
}

ViewportSize View::getViewportSize() const
{
    return mGraphics->getViewportSize();
}

std::string View::windowHandle() const
{
    return mGraphics->windowHandle();
}

void View::initializeGraphics()
{
    mGraphics = new Graphics();
}

void View::createLayers()
{
    createBackgroundLayer();
    
    createGameLayerResources();
    createGameLayer();
    createDoubleupLayer();
}

void View::createGameLayerResources()
{
    mGameResources = new GameLayerResources(mGraphics->getSilverback(), mGraphics->getViewport());
}

void View::createBackgroundLayer()
{
    mBackgroundLayer = new BackgroundLayer(mGraphics->getSilverback(), mGraphics->getViewport());
}

void View::createGameLayer()
{
    mGameLayer = new GameLayer(*mGameResources);
}

void View::createDoubleupLayer()
{
    mDoubleupLayer = new DoubleupLayer(*mGameResources);
}