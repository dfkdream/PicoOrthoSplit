//
// Created by dfkdream on 23. 1. 11.
//

#ifndef ORTHOSPLIT_KEYMATRIX_H
#define ORTHOSPLIT_KEYMATRIX_H

#include "pico/stdlib.h"
#include <vector>
#include <bitset>

class KeyMatrixEventHandler{
public:
    virtual void onPress(int id) = 0;
    virtual void onRelease(int id) = 0;
};

class KeyMatrix {
private:
    std::vector<uint> outputs;
    std::vector<uint> inputs;
    std::vector<bool> pressed;
    KeyMatrixEventHandler& handler;
public:
    KeyMatrix(std::vector<uint> inputs, std::vector<uint> outputs, KeyMatrixEventHandler &handler);
    void run();
};


#endif //ORTHOSPLIT_KEYMATRIX_H
