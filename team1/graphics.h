#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <OGRE/Ogre.h>
#include "Gorilla.h"

class InputInspector;
typedef std::pair<int,int> ViewportSize;

class Graphics : public Ogre::FrameListener
{
public:
    Graphics();
    ~Graphics();
    void setInputInspector(InputInspector& inputInspector);
    void startRendering();
    void Quit();
    
    ViewportSize getViewportSize() const;
    
    Ogre::RenderWindow& getWindow() const;
    Ogre::Viewport& getViewport() const;
    Gorilla::Silverback& getSilverback() const;
    

private: // from Ogre::FrameListener
    bool frameStarted(const Ogre::FrameEvent& evt);
  
private:
    void initializeOgre();
    void createGorilla();

private:
    Gorilla::Silverback*    mSilverback;

    Ogre::Root*             mRoot;
    Ogre::RenderWindow*     mWindow;
    Ogre::Viewport*         mViewport;
    Ogre::SceneManager*     mSceneMgr;
    Ogre::Camera*           mCamera;

    InputInspector*         mInputInspector;

    bool                    mShutDown;
};

#endif // GRAPHICS_H
