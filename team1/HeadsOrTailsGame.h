#ifndef HEADSORTAILS_H
#define HEADSORTAILS_H

class GamePlay;
class Player;

class HeadsOrTailsGame
{
public:
    HeadsOrTailsGame(GamePlay& gamePlay, Player& player);
    virtual ~HeadsOrTailsGame();

    void Play();

private:
    GamePlay& m_gamePlay;
    Player& m_player;
};

#endif //HEADSORTAILS_H
