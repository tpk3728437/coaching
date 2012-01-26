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
        mView.showBaseGameCoin(index, side);
    }
    else if (index > 2)
    {
        mView.showDoubleUpCoin(side);
    }
}

void Controller::onBigWin()
{
    mView.showBigWin();
}

void Controller::onGameWin()
{
    mView.showDoubleUpScreen();
}

void Controller::onGameLoss()
{
    mView.showGameLoss();
}

void Controller::onGameEnd()
{
}

void Controller::onDoubleUp(bool win)
{
    mView.showDoubleupResult(win);
}

void Controller::quitButtonPressed()
{
    mView.quit();
}

void Controller::playButtonPressed()
{
    mView.resetGraphics();
    if (mGameEngine) {
        mGameEngine->play();
    }
}

void Controller::doubleUpButtonPressed()
{
    mView.resetDoubleUpScreenGraphics();
    mDoubleupLogic.doubleUp();
}

void Controller::payoutButtonPressed()
{
    mDoubleupLogic.cashOut();
    mView.resetGraphics();
}
