//
// Created by dfkdream on 23. 1. 11.
//

#ifndef ORTHOSPLIT_STDIO_CDC_H
#define ORTHOSPLIT_STDIO_CDC_H

#include "tusb.h"
#include "pico/stdio/driver.h"

stdio_driver_t cdc_driver{
        .out_chars=reinterpret_cast<void (*)(const char *, int)>(tud_cdc_write),
        .out_flush=reinterpret_cast<void (*)(void)>(tud_cdc_write_flush),
};

#endif //ORTHOSPLIT_STDIO_CDC_H
