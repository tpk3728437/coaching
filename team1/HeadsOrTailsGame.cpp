#include "HeadsOrTailsGame.h"
#include <time.h>
#include <stdlib.h>

HeadsOrTailsGame::HeadsOrTailsGame(GamePlay& gamePlay) : m_gamePlay(gamePlay)
{
}

HeadsOrTailsGame::~HeadsOrTailsGame()
{
}

HeadsOrTailsGame::Side HeadsOrTailsGame::Play()
{
    /* initialize random seed: */
//    srand ( time(0) );

    /* generate secret number: */
//    int result = rand() % 2;
    const int result = m_gamePlay.Flip();

    return (HeadsOrTailsGame::Side) result;
}

