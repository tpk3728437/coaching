#ifndef HEADSORTAILS_H
#define HEADSORTAILS_H

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

private:
    GamePlay& m_gamePlay;
    Player& m_player;
    UserEvents& m_events;
};

#endif //HEADSORTAILS_H
