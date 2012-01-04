#ifndef TRIPLEFLIP_H
#define TRIPLEFLIP_H

#include <OGRE/Ogre.h>
#include "Gorilla.h"

#include "HeadsOrTailsGame.h"
#include "player.h"
#include "doubleuplogic.h"
#include "coinfliplogic.h"
#include "inputhandler.h"


class BackgroundLayer;
class GameLayer;
class DoubleupLayer;
class GameLayerResources;

class TripleFlipApp : public Ogre::FrameListener, private Player, private UserCommandObserver
{
public:    
    TripleFlipApp();
    ~TripleFlipApp();  
    void start();
 
private: // from Ogre::FrameListener
    bool frameStarted(const Ogre::FrameEvent& evt);
  
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
    void initializeOgre();
    void initializeInputHandler();
    void createGorilla();
    void createLayers();
    void createGameLayerResources();
    void createBackgroundLayer();
    void createGameLayer();
    void createDoubleupLayer();
    void createTripleFlipEngine();
 
private:    
    Gorilla::Silverback*    mSilverback;
    BackgroundLayer*        mBackgroundLayer;
    GameLayerResources*     mGameResources;
    GameLayer*              mGameLayer;
    DoubleupLayer*          mDoubleupLayer;

    Ogre::Root*             mRoot;
    Ogre::RenderWindow*     mWindow;
    Ogre::Viewport*         mViewport;
    Ogre::SceneManager*     mSceneMgr;
    Ogre::Camera*           mCamera;
    
    InputHandler*           mInputHandler;
    bool                    mShutDown;

    HeadsOrTailsGame*       mGameEngine;    
    
    DoubleUpLogic           mDoubleupLogic;
    CoinFlipLogic           mCoinFlipLogic;
};

#endif // TRIPLEFLIP_H
