#ifndef HEADSORTAILS_H
#define HEADSORTAILS_H

class HeadsOrTailsGame
{
public:
    HeadsOrTailsGame();
    virtual ~HeadsOrTailsGame();

    enum Side {
        Tails = 0,
        Heads
    };

    HeadsOrTailsGame::Side Play();
};

#endif //HEADSORTAILS_H
