#ifndef HEADSORTAILS_H
#define HEADSORTAILS_H

#include "GameMachine_sm.h"
#include "globals.h"

class GamePlay;
class Player;

class UserEvents
{
public:
    virtual bool DoubleUp() =0;
};

class HeadsOrTailsGame
{
public:
    HeadsOrTailsGame(GamePlay& gamePlay, Player& player, UserEvents& events);
    virtual ~HeadsOrTailsGame();

    void Play();
    
public:
    void playStarted();
    void flipCoin();
    void coinFlipped(Side side);
    void bigWin();
    void gameWin();
    void gameLoss();
    void doubleUp();
    void gameEnd();
    void doubleUpWin(bool win);

private:
    GamePlay& m_gamePlay;
    Player& m_player;
    UserEvents& m_events;
    GameMachineContext m_fsm;
    int numberOfFlips;
};

#endif //HEADSORTAILS_H
