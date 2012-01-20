#ifndef HEADSORTAILS_H
#define HEADSORTAILS_H

#include "GameMachine_sm.h"
#include "globals.h"
#include "gameplay.h"
#include "userevents.h"

class GamePlay;
class Player;

class Game 
{
public:
    virtual void Play() =0;
};

class HeadsOrTailsGame : public Game, private FlipResult, private DoubleupChoiceResult
{
public:
    HeadsOrTailsGame(GamePlay& gamePlay, Player& player, UserEvents& events);
    virtual ~HeadsOrTailsGame();

public: // from game
    void Play();
    
public: // State machine actions
    void playStarted();
    void flipCoin();
    void coinFlipped(Side side);
    void bigWin();
    void gameWin();
    void gameLoss();
    void doesUserWantToDoubleUp();
    void gameEnd();
    void doubleUpWin(bool win);
    void reset();

private: // from FlipResult
    void flipResult(Side side);
    
private: // from DoubleupChoiceResult
    void DoubleUp(bool doubleup);

private:
    GamePlay& m_gamePlay;
    Player& m_player;
    UserEvents& m_events;
    GameMachineContext m_fsm;
    int numberOfFlips;
};

#endif //HEADSORTAILS_H
