#ifndef GAMELAYER_H
#define GAMELAYER_H

#include "gorilla.h"
#include "globals.h"

class LayerFactory;
class GraphicsElement;

class GameLayer
{
public:
    GameLayer(LayerFactory& factory);
    ~GameLayer();
    
    void ResetGraphics();
    void setCoinImage(int index, Side side);
    
    void showBigWin();
    void showLoss();
    void showDoubleupQueryBoxes();

private:
    Gorilla::Screen& Screen();
    void createCoinRectangles(LayerFactory& factory);
    void createWinLogos(LayerFactory& factory);
    void createDoubleupBox(LayerFactory& factory);

private:
    Gorilla::Layer*         mLayer;
    GraphicsElement*        mLogo;        
    typedef std::vector<GraphicsElement*> GraphicsElementVector;
    GraphicsElementVector mCoins;    
    GraphicsElement* mResult;
    GraphicsElement* mDoubleUp;
};

#endif // GAMELAYER_H
