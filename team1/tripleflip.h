#ifndef TRIPLEFLIP_H
#define TRIPLEFLIP_H

#include <OGRE/Ogre.h>
#include <OIS/OIS.h>
#include "Gorilla.h"

#include "HeadsOrTailsGame.h"
#include "gameplay.h"
#include "player.h"
#include "userevents.h"


class TripleFlipApp : public Ogre::FrameListener, public OIS::KeyListener, public OIS::MouseListener, 
        public Player, public GamePlay, public UserEvents
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

private: // UserEvents
     bool DoubleUp();
  
private:  
    void initializeOgre();
    void initializeOIS();
    void createBackground();
    void createCoinSprites();
    void createTripleFlipEngine();
    void setCoinImage(int index, Side side);
    void onCoinFlippedTimerElapse();
    void play();

private:
    Gorilla::Silverback*    mSilverback;
    Gorilla::Screen*        mBackgroundScreen;
    Gorilla::Layer*         mBackgroundLayer;

    Gorilla::Screen*        mScreen;
    Gorilla::Layer*         mLayer;

    Gorilla::Polygon* poly;
    Gorilla::LineList*       list;
    Gorilla::Caption*        caption;
    Gorilla::Rectangle*      rect;
    Gorilla::QuadList*       quads;
    Gorilla::MarkupText*     markup;

    Ogre::Root*             mRoot;
    Ogre::RenderWindow*     mWindow;
    Ogre::Viewport*         mViewport;
    Ogre::SceneManager*     mSceneMgr;
    Ogre::Camera*           mCamera;
    Ogre::Real              mNextUpdate;    
    OIS::InputManager*      mInputManager;
    OIS::Keyboard*          mKeyboard;
    OIS::Mouse*             mMouse; 
    
    Gorilla::Sprite*        mCoinHeadSprite;
    Gorilla::Sprite*        mCoinTailSprite;
    
    HeadsOrTailsGame*       mGameEngine;
    
    FlipResult*             mCoinFlipResultCallback;
    typedef std::vector<Gorilla::Rectangle*> RectangleVector;
    RectangleVector mCoinRectangles;
    
};

#endif // TRIPLEFLIP_H
