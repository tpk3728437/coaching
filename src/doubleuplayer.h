#ifndef DOUBLEUPLAYER_H
#define DOUBLEUPLAYER_H

#include "gorilla.h"
#include "globals.h"

class LayerFactory;
class GraphicsElement;


class DoubleupLayer
{
public:
    DoubleupLayer(LayerFactory& factory);
    ~DoubleupLayer();
    void ResetGraphics();
    void SetCoin(Side side);
    bool IsVisible();
    
    void Show();
    void Hide();
    
    void Result(bool win);

private:
    void ShowDoubleUpQuery();
    void createCoins(LayerFactory& factory);
    void createResultElements(LayerFactory& factory);
    void createDoubleupBox(LayerFactory& factory);

private:
    Gorilla::Layer*         mLayer;
    
    GraphicsElement* mCoin;
    GraphicsElement* mResult;
    GraphicsElement* mDoubleUp;
};

#endif // DOUBLEUPLAYER_H
