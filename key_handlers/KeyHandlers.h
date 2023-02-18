//
// Created by dfkdream on 23. 1. 12.
//

#ifndef ORTHOSPLIT_KEYHANDLERS_H
#define ORTHOSPLIT_KEYHANDLERS_H

#include "../keyboard/keyboard.h"
#include "../key_matrix/KeyMatrix.h"
#include "../layer_handler/LayerHandler.h"

class NormalKeyHandler : public KeyMatrixEventHandler{
protected:
    uint8_t keycode;
    keyboard& kbd;
public:
    NormalKeyHandler(keyboard& kbd, uint8_t keycode);
    void onPress(int id) override;
    void onRelease(int id) override;
};

class ModifierKeyHandler : public NormalKeyHandler{
public:
    ModifierKeyHandler(keyboard& kbd, uint8_t keycode): NormalKeyHandler(kbd, keycode){}
    void onPress(int id) override;
    void onRelease(int id) override;
};

class ConsumerKeyHandler : public NormalKeyHandler{
public:
    ConsumerKeyHandler(keyboard& kbd, uint8_t keycode): NormalKeyHandler(kbd, keycode){}

    void onPress(int id) override;

    void onRelease(int id) override;
};

class SetLayerHandler : public KeyMatrixEventHandler{
private:
    uint layerOnPress;
    uint layerOnRelease;
    LayerHandler& layerHandler;
public:
    SetLayerHandler(LayerHandler& lh, uint onPress, uint onRelease);
    void onPress(int id) override;
    void onRelease(int id) override;
};

class SetLayerPressOnlyHandler : public SetLayerHandler{
public:
    SetLayerPressOnlyHandler(LayerHandler& lh, uint onPress): SetLayerHandler(lh, onPress, onPress){}
    void onRelease(int id) override;
};

class SetLayerReleaseOnlyHandler : public SetLayerHandler{
public:
    SetLayerReleaseOnlyHandler(LayerHandler& lh, uint onRelease): SetLayerHandler(lh, onRelease, onRelease){}
    void onPress(int id) override;
};

class NOOPHandler : public KeyMatrixEventHandler{
public:
    void onPress(int id) override {}
    void onRelease(int id) override {}
};

#endif //ORTHOSPLIT_KEYHANDLERS_H
