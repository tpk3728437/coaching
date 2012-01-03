#ifndef USEREVENTS_H
#define USEREVENTS_H

class DoubleupChoiceResult
{
public:
    virtual void DoubleUp(bool doubleup) =0;
};

class UserEvents
{
public:
    /**
     * Asyncronous doubleup function, result of users choice is reported 
     * through DoubleupChoiceResult interface.
     */ 

    virtual void DoesUserWantToDoubleUp(DoubleupChoiceResult& result) =0;
};

#endif
