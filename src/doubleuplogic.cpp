#include "doubleuplogic.h"


DoubleUpLogic::DoubleUpLogic()
{
    mDoubleUpUserChoiceResultCallback = &mDummyObject;
}

DoubleUpLogic::~DoubleUpLogic()
{
}

void DoubleUpLogic::doubleUp()
{
    mDoubleUpUserChoiceResultCallback->doubleUp(true);
    mDoubleUpUserChoiceResultCallback = &mDummyObject;
}

void DoubleUpLogic::cashOut()
{
    mDoubleUpUserChoiceResultCallback->doubleUp(false);
    mDoubleUpUserChoiceResultCallback = &mDummyObject;
}

void DoubleUpLogic::doesUserWantToDoubleUp(DoubleupChoiceResult& result)
{
    mDoubleUpUserChoiceResultCallback = &result;
}

