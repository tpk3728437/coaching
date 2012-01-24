#ifndef DOUBLEUPLAYER_H
#define DOUBLEUPLAYER_H

#include "Gorilla.h"
#include "globals.h"

class GameLayerResources;

class DoubleupLayer
{
public:
    DoubleupLayer(GameLayerResources& resources);
    ~DoubleupLayer();
    void ResetGraphics();
    void SetCoin(Side side);
    bool IsVisible();
    
    void Show();
    void Hide();
    
    void Result(bool win);

private:
    void ShowDoubleUpQuery();

private:
    Gorilla::Layer*         mLayer;
    GameLayerResources&     mResources;
    
    Gorilla::Rectangle* mCoinRect;
    Gorilla::Rectangle* mResultRect;
    Gorilla::Rectangle* mDoubleUpRect;
};

#endif // DOUBLEUPLAYER_H
