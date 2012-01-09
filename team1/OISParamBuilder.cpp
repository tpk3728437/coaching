#include "OISParamBuilder.h"

OISParamBuilder::OISParamBuilder(Ogre::RenderWindow& window) : mWindow(window)
{
}

OISParamBuilder::~OISParamBuilder()
{
}

OIS::ParamList OISParamBuilder::Build()
{
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;
    mWindow.getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
    return pl;
}
