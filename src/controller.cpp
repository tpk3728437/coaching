#include "controller.h"
#include "headsortailsgame.h"
#include <memory>
#include "view.h"


Controller::Controller(ViewInterface& view) : mView(view), mGameEngine(0)
{
}

Controller::~Controller()
{
}

void Controller::setEngine(Game& gameEngine)
{
    mGameEngine = &gameEngine;
}

UserEvents& Controller::userEventsHandler()
{
    return mDoubleupLogic;
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
    else if (index > 2)
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
    if (mGameEngine) {
        mGameEngine->Play();
    }
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
