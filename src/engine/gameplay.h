#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "globals.h"

class FlipResult
{
public:
    virtual void flipResult(Side side) =0;
};

class GamePlay
{
public:
    /**
     * Asyncronous flip function, result or coin flip is reported through
     * FlipResult interface.
     */ 
    virtual void flip(FlipResult& result) =0;
};

#endif // GAMEPLAY_H
