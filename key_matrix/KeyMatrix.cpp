//
// Created by dfkdream on 23. 1. 11.
//

#include "KeyMatrix.h"

KeyMatrix::KeyMatrix(std::vector<uint> inputs, std::vector<uint> outputs, KeyMatrixEventHandler &handler)
        : handler(handler) {
    this->inputs = inputs;
    this->outputs = outputs;
    this->pressed = std::vector<bool>(inputs.size()*outputs.size(), false);

    for (uint i : outputs){
        gpio_init(i);
        gpio_set_dir(i, GPIO_OUT);
        gpio_put(i, false);
    }

    for (uint i : inputs){
        gpio_init(i);
        gpio_set_dir(i, GPIO_IN);
        gpio_pull_down(i);
    }
}

void KeyMatrix::run() {
    int colN = 0;
    for (uint o: outputs){
        gpio_put(o, true);
        sleep_us(1);

        int rowN = 0;
        for (uint i: inputs){
            int keyID = colN*7+rowN;
            bool value = gpio_get(i);
            if (pressed[keyID]!=value) {
                pressed[keyID] = value;
                if (value) {
                    handler.onPress(keyID);
                } else {
                    handler.onRelease(keyID);
                }
            }
            rowN++;
        }
        gpio_put(o, false);
        colN++;
    }
}