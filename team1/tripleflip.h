#ifndef TRIPLEFLIP_H
#define TRIPLEFLIP_H

#include "HeadsOrTailsGame.h"
#include "player.h"
#include "doubleuplogic.h"
#include "coinfliplogic.h"
#include "inputhandler.h"

class BackgroundLayer;
class GameLayer;
class DoubleupLayer;
class GameLayerResources;
class Graphics;

class TripleFlipApp : private Player, private UserCommandObserver
{
public:
    TripleFlipApp();
    ~TripleFlipApp();  
    void start();
 
private: // from Player
    void onPlayStarted();
    void onCoinFlipped(int index, Side side);
    void onBigWin();
    void onGameWin();
    void onGameLoss();
    void onGameEnd();
    void onDoubleUp(bool win);

private: // from UserCommandObserver
    void QuitButtonPressed();
    void PlayButtonPressed();
    void DoubleUpButtonPressed();
    void PayoutButtonPressed();

private:  
    void initializeGraphics();
    void initializeInputHandler();
    void createLayers();
    void createGameLayerResources();
    void createBackgroundLayer();
    void createGameLayer();
    void createDoubleupLayer();
    void createTripleFlipEngine();
 
private:    
    BackgroundLayer*        mBackgroundLayer;
    GameLayerResources*     mGameResources;
    GameLayer*              mGameLayer;
    DoubleupLayer*          mDoubleupLayer;
    
    InputHandler*           mInputHandler;
    Graphics*               mGraphics;
 
    HeadsOrTailsGame*       mGameEngine;    
    
    DoubleUpLogic           mDoubleupLogic;
    CoinFlipLogic           mCoinFlipLogic;
};

#endif // TRIPLEFLIP_H
