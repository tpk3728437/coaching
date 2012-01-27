#ifndef CONTROLLER_H
#define CONTROLLER_H

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
class Controller : public UserCommandObserver
{
public:
    Controller(ViewInterface& view);
    ~Controller();    
    void setEngine(Game& gameEngine);
    
protected:
    // TODO: callbacks from game logic to drive application logic 
    
protected: // from UserCommandObserver
    void quitButtonPressed();
    void playButtonPressed();
    void doubleUpButtonPressed();
    void payoutButtonPressed();

protected:
    ViewInterface&          mView;
    Game*                   mGameEngine;
};

#endif // CONTROLLER_H
