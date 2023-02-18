//
// Created by dfkdream on 23. 1. 12.
//

#ifndef ORTHOSPLIT_KEYHANDLERFACTORY_H
#define ORTHOSPLIT_KEYHANDLERFACTORY_H

#include "../keyboard/keyboard.h"
#include "../layer_handler/LayerHandler.h"

class KeyHandlerFactory {
private:
    LayerHandler& layerHandler;
    keyboard& kbd;
public:
    KeyHandlerFactory(LayerHandler& l, keyboard& k);
    KeyMatrixEventHandler* n(uint8_t keycode);
    KeyMatrixEventHandler* m(uint8_t keycode);
    KeyMatrixEventHandler* c(uint8_t keycode);
    KeyMatrixEventHandler* sl(uint layerOnPress, uint layerOnRelease);
    KeyMatrixEventHandler* slp(uint layerOnPress);
    KeyMatrixEventHandler* slr(uint layerOnRelease);
    KeyMatrixEventHandler* no();
};


#endif //ORTHOSPLIT_KEYHANDLERFACTORY_H
