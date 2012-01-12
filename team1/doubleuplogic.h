#ifndef DOUBLEUPLOGIC_H
#define DOUBLEUPLOGIC_H

#include "userevents.h"

class DummyDoubleupChoiceResult : public DoubleupChoiceResult
{
    void DoubleUp(bool doubleup) {}
};

class DoubleUpLogic : public UserEvents
{
public:
    DoubleUpLogic();
    ~DoubleUpLogic();

    void DoubleUp();
    void CashOut();
    
private: // UserEvents
     void DoesUserWantToDoubleUp(DoubleupChoiceResult& result);

private:
    DummyDoubleupChoiceResult   mDummyObject;
    DoubleupChoiceResult*       mDoubleUpUserChoiceResultCallback;
};

#endif // DOUBLEUPLOGIC_H

