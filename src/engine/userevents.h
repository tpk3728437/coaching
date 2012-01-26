#ifndef USEREVENTS_H
#define USEREVENTS_H

class DoubleupChoiceResult
{
public:
    virtual void doubleUp(bool doubleup) =0;
};

class UserEvents
{
public:
    /**
     * Asyncronous doubleup function, result of users choice is reported 
     * through DoubleupChoiceResult interface.
     */ 

    virtual void doesUserWantToDoubleUp(DoubleupChoiceResult& result) =0;
};

#endif
