//
// Created by dfkdream on 23. 1. 12.
//

#include "KeyHandlers.h"

NormalKeyHandler::NormalKeyHandler(keyboard &kbd, uint8_t keycode) : kbd(kbd) {
    this->keycode = keycode;
}

void NormalKeyHandler::onPress(int id) {
    kbd.press(keycode);
}

void NormalKeyHandler::onRelease(int id) {
    kbd.release(keycode);
}

void ModifierKeyHandler::onPress(int id) {
    kbd.pressModifier(keycode);
}

void ModifierKeyHandler::onRelease(int id) {
    kbd.releaseModifier(keycode);
}

void ConsumerKeyHandler::onPress(int id) {
    kbd.pressConsumer(keycode);
}

void ConsumerKeyHandler::onRelease(int id) {
    kbd.releaseConsumer();
}

SetLayerHandler::SetLayerHandler(LayerHandler& lh, uint onPress, uint onRelease)
    : layerHandler(lh), layerOnPress(onPress), layerOnRelease(onRelease){}

void SetLayerHandler::onPress(int id) {
    layerHandler.setLayer(layerOnPress);
}

void SetLayerHandler::onRelease(int id) {
    layerHandler.setLayer(layerOnRelease);
}

void SetLayerPressOnlyHandler::onRelease(int id) {
}

void SetLayerReleaseOnlyHandler::onPress(int id) {
}
