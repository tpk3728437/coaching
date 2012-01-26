#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "player.h"
#include "doubleuplogic.h"
#include "coinfliplogic.h"
#include "uitypes.h"
#include "usercommandobserver.h"

class Game;
class ViewInterface;

/**
 * This class is responsible for controlling the application 
 * user interface and the game engine. 
 * The user commands and game engine events drive the application
 * user interface through this class.
 */
class Controller : public Player, public UserCommandObserver
{
public:
    Controller(ViewInterface& view);
    ~Controller();    
    void setEngine(Game& gameEngine);
    UserEvents& userEventsHandler();
    
protected: // from Player
    void onPlayStarted();
    void onCoinFlipped(int index, Side side);
    void onBigWin();
    void onGameWin();
    void onGameLoss();
    void onGameEnd();
    void onDoubleUp(bool win);

protected: // from UserCommandObserver
    void quitButtonPressed();
    void playButtonPressed();
    void doubleUpButtonPressed();
    void payoutButtonPressed();

protected:
    ViewInterface&          mView;
    DoubleUpLogic           mDoubleupLogic;
    Game*                   mGameEngine;
};

#endif // CONTROLLER_H
