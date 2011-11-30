#ifndef HEADSORTAILS_H
#define HEADSORTAILS_H

class GamePlay
{
public:
    virtual int Flip() const =0;
};

class HeadsOrTailsGame
{
public:
    HeadsOrTailsGame(GamePlay& gamePlay);
    virtual ~HeadsOrTailsGame();

    enum Side {
        Tails = 0,
        Heads
    };

    HeadsOrTailsGame::Side Play();

private:
    GamePlay& m_gamePlay;
};

#endif //HEADSORTAILS_H
