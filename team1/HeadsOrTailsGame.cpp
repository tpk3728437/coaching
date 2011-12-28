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
    m_events(events),
    m_fsm(*this),
    numberOfFlips(-1)
{
}

HeadsOrTailsGame::~HeadsOrTailsGame()
{
}

void HeadsOrTailsGame::Play()
{
    m_fsm.enterStartState();    
}

void HeadsOrTailsGame::playStarted() 
{
    m_player.onPlayStarted();
}
    
void HeadsOrTailsGame::flipCoin() 
{
    const Side result = (Side) m_gamePlay.Flip();
    ++numberOfFlips;
    if (result == Heads)
    {
        m_fsm.head();
    }
    else
    {
        m_fsm.tail();
    }
}

void HeadsOrTailsGame::coinFlipped(Side side)
{
    m_player.onCoinFlipped(numberOfFlips, side);
}

void HeadsOrTailsGame::gameLoss()
{
    m_player.onGameLoss();
    m_fsm.end();
}

void HeadsOrTailsGame::doubleUp()
{
    if ( m_events.DoubleUp())
    {
        m_fsm.doubleUp();
    }
    else
    {
        m_fsm.end();
    }
}

void HeadsOrTailsGame::bigWin()
{
    m_player.onBigWin();
    m_fsm.end();
}

void HeadsOrTailsGame::gameWin()
{
    m_player.onGameWin();        
}
    
void HeadsOrTailsGame::gameEnd()
{
    m_player.onGameEnd();        
}

void HeadsOrTailsGame::doubleUpWin(bool win)
{
    m_player.onDoubleUp(win);
}
