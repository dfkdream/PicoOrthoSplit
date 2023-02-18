//
// Created by dfkdream on 23. 1. 12.
//

#include "KeyHandlerFactory.h"
#include "KeyHandlers.h"

KeyHandlerFactory::KeyHandlerFactory(LayerHandler &l, keyboard &k)
    :layerHandler(l), kbd(k){}

KeyMatrixEventHandler *KeyHandlerFactory::n(uint8_t keycode) {
    return new NormalKeyHandler(kbd, keycode);
}

KeyMatrixEventHandler *KeyHandlerFactory::m(uint8_t keycode) {
    return new ModifierKeyHandler(kbd, keycode);
}

KeyMatrixEventHandler *KeyHandlerFactory::c(uint8_t keycode) {
    return new ConsumerKeyHandler(kbd, keycode);
}

KeyMatrixEventHandler *KeyHandlerFactory::sl(uint layerOnPress, uint layerOnRelease) {
    return new SetLayerHandler(layerHandler, layerOnPress, layerOnRelease);
}

KeyMatrixEventHandler *KeyHandlerFactory::slp(uint layerOnPress) {
    return new SetLayerPressOnlyHandler(layerHandler, layerOnPress);
}

KeyMatrixEventHandler *KeyHandlerFactory::slr(uint layerOnRelease) {
    return new SetLayerReleaseOnlyHandler(layerHandler, layerOnRelease);
}

KeyMatrixEventHandler *KeyHandlerFactory::no() {
    return new NOOPHandler;
}

