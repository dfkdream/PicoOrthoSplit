//
// Created by dfkdream on 23. 1. 11.
//

#ifndef ORTHOSPLIT_LAYERHANDLER_H
#define ORTHOSPLIT_LAYERHANDLER_H

#include "../key_matrix/KeyMatrix.h"
#include "../keyboard/keyboard.h"

class LayerHandler : public KeyMatrixEventHandler{
private:
   std::vector<std::vector<KeyMatrixEventHandler*>> layers;
   uint currentLayer = 0;
public:
    explicit LayerHandler(int initialLayer);

    void addLayer(std::vector<KeyMatrixEventHandler*> layer);
    void setLayer(uint layer);

    void onPress(int id) override;

    void onRelease(int id) override;
};


#endif //ORTHOSPLIT_LAYERHANDLER_H
