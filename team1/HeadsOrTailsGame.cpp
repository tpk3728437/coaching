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
    // signal player onPlayStarted()
    m_player.onPlayStarted();


    // state machine
    // flip one coin, then signal player that coin has been flipped with result
    const Side firstResult = (Side) m_gamePlay.Flip();
    m_player.onCoinFlipped(0, firstResult);

    const Side secondResult = (Side) m_gamePlay.Flip();
    m_player.onCoinFlipped(1, secondResult);

    // signal player Game Loss
    m_player.onGameLoss();
    
    // signal game end
    m_player.onGameEnd();
        
        // 
        //virtual void onGameWin() =0;
        //virtual void onGameEnd() =0;

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

