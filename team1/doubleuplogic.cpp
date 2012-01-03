#include "doubleuplogic.h"


DoubleUpLogic::DoubleUpLogic()
{
    mDoubleUpUserChoiceResultCallback = &mDummyObject;
}

DoubleUpLogic::~DoubleUpLogic()
{
}

void DoubleUpLogic::DoubleUp()
{
    mDoubleUpUserChoiceResultCallback->DoubleUp(true);
    mDoubleUpUserChoiceResultCallback = &mDummyObject;
}

void DoubleUpLogic::CashOut()
{
    mDoubleUpUserChoiceResultCallback->DoubleUp(false);
    mDoubleUpUserChoiceResultCallback = &mDummyObject;
}

void DoubleUpLogic::DoesUserWantToDoubleUp(DoubleupChoiceResult& result)
{
    mDoubleUpUserChoiceResultCallback = &result;
}

