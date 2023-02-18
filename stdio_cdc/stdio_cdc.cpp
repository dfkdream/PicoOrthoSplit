//
// Created by dfkdream on 23. 1. 11.
//

#include "stdio_cdc.h"

// Invoked when CDC interface received data from host
void tud_cdc_rx_cb(uint8_t itf)
{
    (void) itf;

    char buf[64];
    uint32_t count = tud_cdc_read(buf, sizeof(buf));

    // TODO control LED on keyboard of host stack
    (void) count;
}
