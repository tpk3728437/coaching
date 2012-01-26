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
    void resetGraphics();
    void setCoin(Side side);
    bool isVisible();
    
    void show();
    void hide();
    
    void result(bool win);

private:
    void showDoubleUpQuery();
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
