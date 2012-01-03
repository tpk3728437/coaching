#ifndef TRIPLEFLIP_H
#define TRIPLEFLIP_H

#include <OGRE/Ogre.h>
#include <OIS/OIS.h>
#include "Gorilla.h"

#include "HeadsOrTailsGame.h"
#include "gameplay.h"
#include "player.h"
#include "userevents.h"
#include "doubleuplogic.h"

class BackgroundLayer;
class GameLayer;
class DoubleupLayer;


class TripleFlipApp : public Ogre::FrameListener, public OIS::KeyListener, public OIS::MouseListener, 
        public Player, public GamePlay
{
public:    
    TripleFlipApp();
    ~TripleFlipApp();  
    void start();
 
private:
    bool frameStarted(const Ogre::FrameEvent& evt);
    bool keyPressed( const OIS::KeyEvent &e );
    bool keyReleased( const OIS::KeyEvent &e );
    bool mouseMoved( const OIS::MouseEvent &arg );
    bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
  
private: // from GamePlay  
    void Flip(FlipResult& result);

private: // from Player
    void onPlayStarted();
    void onCoinFlipped(int index, Side side);
    void onBigWin();
    void onGameWin();
    void onGameLoss();
    void onGameEnd();
    void onDoubleUp(bool win);

private:  
    void initializeOgre();
    void initializeOIS();
    void createGorilla();
    void createLayers();
    void createBackgroundLayer();
    void createGameLayer();
    void createDoubleupLayer();
    void createTripleFlipEngine();
    void onCoinFlippedTimerElapse();
    void play();

private:
    Gorilla::Silverback*    mSilverback;
    BackgroundLayer*        mBackgroundLayer;
    GameLayer*              mGameLayer;
    DoubleupLayer*          mDoubleupLayer;

    Ogre::Root*             mRoot;
    Ogre::RenderWindow*     mWindow;
    Ogre::Viewport*         mViewport;
    Ogre::SceneManager*     mSceneMgr;
    Ogre::Camera*           mCamera;
    OIS::InputManager*      mInputManager;
    OIS::Keyboard*          mKeyboard;
    OIS::Mouse*             mMouse; 
    
    HeadsOrTailsGame*       mGameEngine;    
    FlipResult*             mCoinFlipResultCallback;
    
    DoubleUpLogic           mDoubleupLogic;
    

};

#endif // TRIPLEFLIP_H
