#include "HeadsOrTailsGame.h"
#include <time.h>
#include <stdlib.h>

HeadsOrTailsGame::HeadsOrTailsGame()
{
}

HeadsOrTailsGame::~HeadsOrTailsGame()
{
}

HeadsOrTailsGame::Side HeadsOrTailsGame::Play()
{
    /* initialize random seed: */
    srand ( time(0) );

    /* generate secret number: */
    int result = rand() % 2;

    return (HeadsOrTailsGame::Side) result;
}

