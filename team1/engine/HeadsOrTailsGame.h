#ifndef HEADSORTAILS_H
#define HEADSORTAILS_H

#include "GameMachine_sm.h"
#include "globals.h"
#include "gameplay.h"

class GamePlay;
class Player;
class UserEvents;


class HeadsOrTailsGame : private FlipResult
{
public:
    HeadsOrTailsGame(GamePlay& gamePlay, Player& player, UserEvents& events);
    virtual ~HeadsOrTailsGame();

    void Play();
    
public: // State machine actions
    void playStarted();
    void flipCoin();
    void coinFlipped(Side side);
    void bigWin();
    void gameWin();
    void gameLoss();
    void doubleUp();
    void gameEnd();
    void doubleUpWin(bool win);
    void reset();

private: // from FlipResult
    void flipResult(Side side);

private:
    GamePlay& m_gamePlay;
    Player& m_player;
    UserEvents& m_events;
    GameMachineContext m_fsm;
    int numberOfFlips;
};

#endif //HEADSORTAILS_H
