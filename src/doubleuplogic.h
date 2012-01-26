#ifndef DOUBLEUPLOGIC_H
#define DOUBLEUPLOGIC_H

#include "userevents.h"

class DummyDoubleupChoiceResult : public DoubleupChoiceResult
{
    void doubleUp(bool /*doubleup*/) {}
};

/**
 * This class is responsible for routing the user doubleup
 * selection to the UserEvents interface callback. 
 * When no query is active, the call is simply ignored by 
 * the dummy object. 
 */ 
class DoubleUpLogic : public UserEvents
{
public:
    DoubleUpLogic();
    ~DoubleUpLogic();

    void doubleUp();
    void cashOut();
    
private: // UserEvents
     void doesUserWantToDoubleUp(DoubleupChoiceResult& result);

private:
    DummyDoubleupChoiceResult   mDummyObject;
    DoubleupChoiceResult*       mDoubleUpUserChoiceResultCallback;
};

#endif // DOUBLEUPLOGIC_H

