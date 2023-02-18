//
// Created by dfkdream on 22. 12. 30.
//

#include "pico/stdlib.h"
#include "tusb.h"
#include "keyboard/keyboard.h"
#include "stdio_cdc/stdio_cdc.h"
#include "key_matrix/KeyMatrix.h"
#include "key_handlers/KeyHandlerFactory.h"
#include "layer_handler/LayerHandler.h"
#include "hid_host/HIDHost.h"

#define KEYBOARD_LEFT 0
#define KEYBOARD_RIGHT 1

int main() {
    stdio_set_driver_enabled(&cdc_driver, true);
    stdio_set_translate_crlf(&cdc_driver, true);

    tud_init(0);

    keyboard kbd;
    HIDHost host(kbd);

    LayerHandler lh(KEYBOARD_LEFT);
    KeyMatrix mat({12, 11, 10, 9, 8, 7, 6}, {22, 21, 20, 19, 18}, lh);

    KeyHandlerFactory f(lh, kbd);

    // Normal Left layer (0)
    lh.addLayer({
                        f.n(HID_KEY_ESCAPE),f.n(HID_KEY_1),f.n(HID_KEY_2),f.n(HID_KEY_3),f.n(HID_KEY_4),f.n(HID_KEY_5),f.n(HID_KEY_6),
                        f.n(HID_KEY_TAB),f.n(HID_KEY_Q),f.n(HID_KEY_W),f.n(HID_KEY_E),f.n(HID_KEY_R),f.n(HID_KEY_T),f.n(HID_KEY_Y),
                        f.m(KEYBOARD_MODIFIER_LEFTCTRL),f.m(KEYBOARD_MODIFIER_LEFTCTRL),f.n(HID_KEY_A),f.n(HID_KEY_S),f.n(HID_KEY_D),f.n(HID_KEY_F),f.n(HID_KEY_G),
                        f.m(KEYBOARD_MODIFIER_LEFTSHIFT),f.m(KEYBOARD_MODIFIER_LEFTSHIFT),f.n(HID_KEY_Z),f.n(HID_KEY_X),f.n(HID_KEY_C),f.n(HID_KEY_V),f.n(HID_KEY_B),
                        f.m(KEYBOARD_MODIFIER_LEFTALT),f.m(KEYBOARD_MODIFIER_LEFTGUI),f.n(HID_KEY_SPACE),f.n(HID_KEY_SPACE),f.n(HID_KEY_SPACE),f.n(HID_KEY_SPACE),f.slp(3),
                });

    // Normal Right layer (1)
    lh.addLayer({
                        f.n(HID_KEY_7),f.n(HID_KEY_8),f.n(HID_KEY_9),f.n(HID_KEY_0),f.n(HID_KEY_MINUS),f.n(HID_KEY_BACKSLASH),f.n(HID_KEY_GRAVE),
                        f.n(HID_KEY_U),f.n(HID_KEY_I),f.n(HID_KEY_O),f.n(HID_KEY_P),f.n(HID_KEY_BRACKET_LEFT),f.n(HID_KEY_BRACKET_RIGHT),f.n(HID_KEY_BACKSPACE),
                        f.n(HID_KEY_H),f.n(HID_KEY_J),f.n(HID_KEY_K),f.n(HID_KEY_L),f.n(HID_KEY_SEMICOLON),f.n(HID_KEY_APOSTROPHE),f.n(HID_KEY_ENTER),
                        f.n(HID_KEY_N),f.n(HID_KEY_M),f.n(HID_KEY_COMMA),f.n(HID_KEY_PERIOD),f.n(HID_KEY_SLASH),f.m(KEYBOARD_MODIFIER_RIGHTSHIFT),f.m(KEYBOARD_MODIFIER_RIGHTSHIFT),
                        f.slp(4),f.n(HID_KEY_SPACE),f.n(HID_KEY_SPACE),f.n(HID_KEY_SPACE),f.n(HID_KEY_SPACE),f.m(KEYBOARD_MODIFIER_RIGHTGUI),f.m(KEYBOARD_MODIFIER_RIGHTALT),
                });

    // Keypad and Arrow layer (2)
    lh.addLayer({
                        f.n(HID_KEY_TAB),f.n(HID_KEY_KEYPAD_DIVIDE),f.n(HID_KEY_KEYPAD_MULTIPLY),f.n(HID_KEY_BACKSPACE),f.no(),f.no(),f.no(),
                        f.n(HID_KEY_KEYPAD_7),f.n(HID_KEY_KEYPAD_8),f.n(HID_KEY_KEYPAD_9),f.n(HID_KEY_KEYPAD_SUBTRACT),f.no(),f.n(HID_KEY_ARROW_UP),f.no(),
                        f.n(HID_KEY_KEYPAD_4),f.n(HID_KEY_KEYPAD_5),f.n(HID_KEY_KEYPAD_6),f.n(HID_KEY_KEYPAD_ADD),f.n(HID_KEY_ARROW_LEFT),f.n(HID_KEY_ARROW_DOWN),f.n(HID_KEY_ARROW_RIGHT),
                        f.n(HID_KEY_KEYPAD_1),f.n(HID_KEY_KEYPAD_2),f.n(HID_KEY_KEYPAD_3),f.n(HID_KEY_KEYPAD_ENTER),f.no(),f.no(),f.no(),
                        f.slp(1),f.n(HID_KEY_KEYPAD_0),f.n(HID_KEY_KEYPAD_COMMA),f.n(HID_KEY_KEYPAD_ENTER),f.no(),f.no(),f.slp(0),
                });

    // Left layer select layer (3)
    lh.addLayer({
                        f.n(HID_KEY_INSERT), f.n(HID_KEY_F1), f.n(HID_KEY_F2), f.n(HID_KEY_F3), f.n(HID_KEY_F4), f.n(HID_KEY_F5), f.n(HID_KEY_F6),
                        f.n(HID_KEY_CAPS_LOCK), f.no(), f.no(), f.no(), f.no(), f.no(), f.no(),
                        f.no(), f.no(), f.c(HID_USAGE_CONSUMER_VOLUME_DECREMENT), f.c(HID_USAGE_CONSUMER_VOLUME_INCREMENT), f.no(), f.no(), f.no(),
                        f.no(), f.no(), f.c(HID_USAGE_CONSUMER_BRIGHTNESS_DECREMENT), f.c(HID_USAGE_CONSUMER_BRIGHTNESS_INCREMENT), f.no(), f.no(), f.no(),
                        f.slp(1), f.no(), f.no(), f.no(), f.no(), f.slp(2), f.slr(0),
                });

    // Right layer select layer (4)
    lh.addLayer({
                        f.n(HID_KEY_F7), f.n(HID_KEY_F8), f.n(HID_KEY_F9), f.n(HID_KEY_F10), f.n(HID_KEY_F11), f.n(HID_KEY_F12), f.n(HID_KEY_DELETE),
                        f.no(), f.no(), f.no(), f.no(), f.no(), f.no(), f.no(),
                        f.n(HID_KEY_ARROW_LEFT), f.n(HID_KEY_ARROW_DOWN), f.n(HID_KEY_ARROW_UP), f.n(HID_KEY_ARROW_RIGHT), f.no(), f.no(), f.no(),
                        f.no(), f.no(), f.no(), f.no(), f.no(), f.no(), f.no(),
                        f.slr(1), f.slp(2), f.no(), f.no(), f.no(), f.no(), f.slp(0),
                });


    while(true){
        kbd.run();
        mat.run();
        tud_cdc_write_flush();
    }

    return 0;
}
