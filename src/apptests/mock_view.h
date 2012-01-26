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
    MOCK_METHOD0(quit, void());
    MOCK_METHOD1(setInputInspector, void(InputInspector& inputInspector));    
    MOCK_METHOD0(resetGraphics, void());
    MOCK_METHOD0(showDoubleUpScreen, void());
    MOCK_METHOD0(resetDoubleUpScreenGraphics, void());
    MOCK_METHOD1(showDoubleupResult, void(bool win));
    MOCK_METHOD0(showGameLoss, void());
    MOCK_METHOD0(showBigWin, void());
    MOCK_METHOD2(showBaseGameCoin, void(int index, Side side));
    MOCK_METHOD1(showDoubleUpCoin, void(Side side));
    MOCK_CONST_METHOD0(getViewportSize, ViewportSize());
    MOCK_CONST_METHOD0(windowHandle, std::string());
};


#endif // MOCK_VIEW_H
