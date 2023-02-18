#ifndef MPKEYPAD_KEYBOARD_H
#define MPKEYPAD_KEYBOARD_H

#include "pico/stdlib.h"
#include <set>
#include "pico/mutex.h"


class keyboard {
public:
    keyboard();
    void run();
    bool press(uint8_t keycode);
    bool release(uint8_t keycode);
    bool releaseAll();
    bool pressModifier(uint8_t keycode);
    bool releaseModifier(uint8_t keycode);
    bool applyModifier(uint8_t keycode);
    bool pressConsumer(uint16_t keycode);
    bool releaseConsumer();
private:
    std::set<uint8_t> pressed;
    uint8_t modifier = 0;
    void pressAll();
    mutex_t *mtx;
    bool hasConsumer = false;
};


#endif //MPKEYPAD_KEYBOARD_H
