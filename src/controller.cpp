#include "controller.h"
#include "headsortailsgame.h"
#include <memory>
#include "view.h"
#include <iostream>


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

void Controller::quitButtonPressed()
{
    mView.quit();
}

void Controller::playButtonPressed()
{
    std::cout << "Play button pressed" << std::endl;
    mView.resetGraphics();
    if (mGameEngine) {
        mGameEngine->play();
    }
}

void Controller::doubleUpButtonPressed()
{
    std::cout << "tuplausnappia painettu" << std::endl;

    // TODO: Käyttäjä on painanut tuplausnappia, siirry tuplaustilaan
    mView.resetDoubleUpScreenGraphics();
}

void Controller::payoutButtonPressed()
{
    std::cout << "voittojen lunastusnappia painettu" << std::endl;

    // TODO: käyttäjä on painanut voittojen lunastus nappia
    // siirry tuplaustilasta pois
    mView.resetGraphics();
}
