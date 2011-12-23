#include "HeadsOrTailsGame.h"
#include <time.h>
#include <stdlib.h>
#include "gameplay.h"
#include "player.h"

    // started->oneWin
    // started->oneLoss
    // oneWin->twoWin
    // twoWin -> BigWin
    // twoWin->doubleUp
    // doubleUp->doubleUp
    // oneLoss-> oneWin
    // oneLoss -> twoLoss
    // twoLoss -> endGame
    // doubleUp -> endGame
    // bigWin -> endGame 

HeadsOrTailsGame::HeadsOrTailsGame(GamePlay& gamePlay, Player& player, UserEvents& events) : 
    m_gamePlay(gamePlay),
    m_player(player),
    m_events(events)
{
}

HeadsOrTailsGame::~HeadsOrTailsGame()
{
}

void HeadsOrTailsGame::Play()
{
    int numberOfHeads = 0;

    m_player.onPlayStarted();

    // state machine
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
        if (numberOfHeads == 3) 
        {
            m_player.onBigWin();
        }
        m_player.onGameWin();        

        if ( numberOfHeads == 2) { 
            if (m_events.DoubleUp())
            {
            const Side result = (Side) m_gamePlay.Flip();
            m_player.onDoubleUp(result == Heads);
            m_player.onCoinFlipped(3, result);
            }
        }
    }
    else
    {
        m_player.onGameLoss();
    }
    
    m_player.onGameEnd();        
}
