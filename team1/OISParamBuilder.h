#ifndef OISPARAMBUILDER_H
#define OISPARAMBUILDER_H

#include <OGRE/Ogre.h>
#include <OIS/OIS.h>

class OISParamBuilder
{
public:
    OISParamBuilder(Ogre::RenderWindow& window);
    ~OISParamBuilder();

    OIS::ParamList Build();
    
private:
    Ogre::RenderWindow& mWindow;
};

#endif // OISPARAMBUILDER_H
