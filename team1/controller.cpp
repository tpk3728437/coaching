#include "controller.h"
#include "oisinputmanager.h"
#include "HeadsOrTailsGame.h"
#include <memory>
#include "view.h"


Controller::Controller(View& view) : mView(view), mGameEngine(0), mInputHandler(0)
{
    initializeInputHandler();
}

Controller::~Controller()
{
    delete mInputHandler;
}

void Controller::setEngine(HeadsOrTailsGame& gameEngine)
{
    mGameEngine = &gameEngine;
}

UserEvents& Controller::userEventsHandler()
{
    return mDoubleupLogic;
}

void Controller::initializeInputHandler()
{
    ViewportSize size = mView.getViewportSize();
    std::auto_ptr<InputManager> inputManager(new OISInputManager(mView.windowHandle(), size));
    mInputHandler = new InputHandler(inputManager, *this);
    
    mView.setInputInspector(*mInputHandler);
}

void Controller::onPlayStarted()
{
}

void Controller::onCoinFlipped(int index, Side side)
{
    if (index >= 0 && index <= 2)
    {
        mView.ShowBaseGameCoin(index, side);
    }
    else
    {
        mView.ShowDoubleUpCoin(side);
    }
}

void Controller::onBigWin()
{
    mView.ShowBigWin();
}

void Controller::onGameWin()
{
    mView.ShowDoubleUpScreen();
}

void Controller::onGameLoss()
{
    mView.ShowGameLoss();
}

void Controller::onGameEnd()
{
}

void Controller::onDoubleUp(bool win)
{
    mView.ShowDoubleupResult(win);
}

void Controller::QuitButtonPressed()
{
    mView.Quit();
}

void Controller::PlayButtonPressed()
{
    mView.ResetGraphics();
    mGameEngine->Play();          
}

void Controller::DoubleUpButtonPressed()
{
    mView.ResetDoubleUpScreenGraphics();
    mDoubleupLogic.DoubleUp();
}

void Controller::PayoutButtonPressed()
{
    mDoubleupLogic.CashOut();
    mView.ResetGraphics();
}
