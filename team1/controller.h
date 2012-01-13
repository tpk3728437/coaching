#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "player.h"
#include "inputhandler.h"
#include "doubleuplogic.h"
#include "coinfliplogic.h"

class HeadsOrTailsGame;
class View;

/**
 * This class is responsible for controlling the application 
 * user interface and the game engine. 
 * The user commands and game engine events drive the application
 * user interface through this class.
 */
class Controller : public Player, private UserCommandObserver
{
public:
    Controller(View& view);
    ~Controller();    
    void setEngine(HeadsOrTailsGame& gameEngine);
    UserEvents& userEventsHandler();
    
private: // from Player
    void onPlayStarted();
    void onCoinFlipped(int index, Side side);
    void onBigWin();
    void onGameWin();
    void onGameLoss();
    void onGameEnd();
    void onDoubleUp(bool win);

private: // from UserCommandObserver
    void QuitButtonPressed();
    void PlayButtonPressed();
    void DoubleUpButtonPressed();
    void PayoutButtonPressed();    
    
private:
    void initializeInputHandler();
    
private:
    View&                   mView;
    DoubleUpLogic           mDoubleupLogic;
    InputHandler*           mInputHandler;
    HeadsOrTailsGame*       mGameEngine;
};

#endif // CONTROLLER_H
