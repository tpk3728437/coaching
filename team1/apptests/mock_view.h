#ifndef MOCK_VIEW_H
#define MOCK_VIEW_H

#include <gmock/gmock.h>
#include "viewinterface.h"


class MockView : public ViewInterface
{
public:
    MockView() {}
    ~MockView() {}
    MOCK_METHOD0(startRendering, void());
    MOCK_METHOD0(Quit, void());
    MOCK_METHOD1(setInputInspector, void(InputInspector& inputInspector));    
    MOCK_METHOD0(ResetGraphics, void());
    MOCK_METHOD0(ShowDoubleUpScreen, void());
    MOCK_METHOD0(ResetDoubleUpScreenGraphics, void());
    MOCK_METHOD1(ShowDoubleupResult, void(bool win));
    MOCK_METHOD0(ShowGameLoss, void());
    MOCK_METHOD0(ShowBigWin, void());
    MOCK_METHOD2(ShowBaseGameCoin, void(int index, Side side));
    MOCK_METHOD1(ShowDoubleUpCoin, void(Side side));    
    MOCK_CONST_METHOD0(getViewportSize, ViewportSize());
    MOCK_CONST_METHOD0(windowHandle, std::string());
};


#endif // MOCK_VIEW_H
