#ifndef HEADSORTAILS_H
#define HEADSORTAILS_H

#include "globals.h"

class GamePlay;
class Player;

class Game 
{
public:
    virtual void play() =0;
};

/**
 * This class is responsible for implementing the 
 * game logic.
 */ 
class HeadsOrTailsGame : public Game
{
public:
    HeadsOrTailsGame();
    virtual ~HeadsOrTailsGame();

public: // from game
    void play();
    
private: // data members

};

#endif //HEADSORTAILS_H
