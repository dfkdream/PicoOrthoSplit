//
// Created by dfkdream on 23. 1. 11.
//

#include "LayerHandler.h"

LayerHandler::LayerHandler(int initialLayer): currentLayer(initialLayer){}

void LayerHandler::setLayer(uint layer) {
    currentLayer = layer;
    printf("Set layer: %d\n", layer);
}

void LayerHandler::onPress(int id) {
    layers[currentLayer][id]->onPress(id);
}

void LayerHandler::onRelease(int id) {
    layers[currentLayer][id]->onRelease(id);
}

void LayerHandler::addLayer(std::vector<KeyMatrixEventHandler *> layer) {
    layers.push_back(layer);
}
