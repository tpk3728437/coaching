#include "HeadsOrTailsGame.h"
#include <time.h>
#include <stdlib.h>
#include "gameplay.h"
#include "player.h"


HeadsOrTailsGame::HeadsOrTailsGame(GamePlay& gamePlay, Player& player) : 
    m_gamePlay(gamePlay),
    m_player(player)
{
}

HeadsOrTailsGame::~HeadsOrTailsGame()
{
}

void HeadsOrTailsGame::Play()
{
    int numberOfHeads = 0;
    // signal player onPlayStarted()
    m_player.onPlayStarted();

    // state machine
    // flip one coin, then signal player that coin has been flipped with result
    const Side firstResult = (Side) m_gamePlay.Flip();
    if (firstResult == Heads) 
    {
        ++numberOfHeads;
    }
    m_player.onCoinFlipped(0, firstResult);

    const Side secondResult = (Side) m_gamePlay.Flip();
    if (secondResult == Heads) 
    {
        ++numberOfHeads;
    }
    m_player.onCoinFlipped(1, secondResult);

    if (numberOfHeads >= 1)
    {
        const Side thirdResult = (Side) m_gamePlay.Flip();
        if (thirdResult == Heads) 
        {
            ++numberOfHeads;
        }
        m_player.onCoinFlipped(2, thirdResult);
    }

    if ( numberOfHeads >= 2) 
    {
        m_player.onGameWin();        
    }
    else
    {
        // signal player Game Loss
        m_player.onGameLoss();
    }
    
    // signal game end
    m_player.onGameEnd();
        
    // started->oneWin
    // started->oneLoss
    // oneWin->twoWin
    // twoWin->doubleUp
    // doubleUp->doubleUp
    // oneLoss-> oneWin
    // oneLoss -> twoLoss
    // twoLoss -> endGame
    // twoWin -> endGame 

}

