//
// Created by dfkdream on 23. 1. 12.
//

#ifndef ORTHOSPLIT_HIDHOST_H
#define ORTHOSPLIT_HIDHOST_H

#include "../keyboard/keyboard.h"
#include "tusb.h"


class HIDHost {
private:
    keyboard& kbd;
    hid_keyboard_report_t prev_report = {0, 0, {0,}};
public:
    HIDHost(keyboard& kbd);

    void onReport(hid_keyboard_report_t const *report);
};


#endif //ORTHOSPLIT_HIDHOST_H
