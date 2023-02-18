//
// Created by dfkdream on 23. 1. 12.
//

#include "HIDHost.h"

#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pio_usb.h"
#include "tusb.h"

HIDHost* host = nullptr;

// look up new key in previous keys
static inline bool find_key_in_report(hid_keyboard_report_t const *report, uint8_t keycode)
{
    for(uint8_t i=0; i<6; i++)
    {
        if (report->keycode[i] == keycode)  return true;
    }

    return false;
}

void core1_main() {
    sleep_ms(10);

    // Use tuh_configure() to pass pio configuration to the host stack
    // Note: tuh_configure() must be called before
    pio_usb_configuration_t pio_cfg = PIO_USB_DEFAULT_CONFIG;
    tuh_configure(1, TUH_CFGID_RPI_PIO_USB_CONFIGURATION, &pio_cfg);

    // To run USB SOF interrupt in core1, init host stack for pio_usb (roothub
    // port1) on core1
    tuh_init(1);

    while (true) {
        tuh_task(); // tinyusb host task
    }
}

HIDHost::HIDHost(keyboard &kbd): kbd(kbd) {
    set_sys_clock_khz(120000, true);
    sleep_ms(10);
    host = this;
    multicore_reset_core1();
    multicore_launch_core1(core1_main);
}

void HIDHost::onReport(const hid_keyboard_report_t *report) {
    printf("Host: [ %02X %02X ", report->modifier, report->reserved);
    kbd.applyModifier(report->modifier);

    for (auto i : report->keycode){
        printf("%02X ", i);
        if (!find_key_in_report(&prev_report, i)) kbd.press(i);
    }

    for (auto i : prev_report.keycode){
        if (!find_key_in_report(report, i)) kbd.release(i);
    }
    printf("]\n");


    prev_report = *report;
}

//--------------------------------------------------------------------+
// Host HID
//--------------------------------------------------------------------+

// Invoked when device with hid interface is mounted
// Report descriptor is also available for use. tuh_hid_parse_report_descriptor()
// can be used to parse common/simple enough descriptor.
// Note: if report descriptor length > CFG_TUH_ENUMERATION_BUFSIZE, it will be skipped
// therefore report_desc = NULL, desc_len = 0
void tuh_hid_mount_cb(uint8_t dev_addr, uint8_t instance, uint8_t const* desc_report, uint16_t desc_len)
{
    (void)desc_report;
    (void)desc_len;

    // Interface protocol (hid_interface_protocol_enum_t)
    const char* protocol_str[] = { "None", "Keyboard", "Mouse" };
    uint8_t const itf_protocol = tuh_hid_interface_protocol(dev_addr, instance);

    uint16_t vid, pid;
    tuh_vid_pid_get(dev_addr, &vid, &pid);

    printf("[%04x:%04x][%u] HID Interface%u, Protocol = %s\r\n", vid, pid, dev_addr, instance, protocol_str[itf_protocol]);

    // Receive report from boot keyboard & mouse only
    // tuh_hid_report_received_cb() will be invoked when report is available
    if (itf_protocol == HID_ITF_PROTOCOL_KEYBOARD || itf_protocol == HID_ITF_PROTOCOL_MOUSE)
    {
        if ( !tuh_hid_receive_report(dev_addr, instance) )
        {
            printf("Error: cannot request report\r\n");
        }
    }
}

// Invoked when device with hid interface is un-mounted
void tuh_hid_umount_cb(uint8_t dev_addr, uint8_t instance)
{
    printf("[%u] HID Interface%u is unmounted\r\n", dev_addr, instance);
}

// Invoked when received report from device via interrupt endpoint
void tuh_hid_report_received_cb(uint8_t dev_addr, uint8_t instance, uint8_t const* report, uint16_t len)
{
    (void) len;
    uint8_t const itf_protocol = tuh_hid_interface_protocol(dev_addr, instance);

    if (itf_protocol == HID_ITF_PROTOCOL_KEYBOARD)
    {
        if (host) host->onReport((hid_keyboard_report_t const*)(report+1));
    }

    // continue to request to receive report
    if ( !tuh_hid_receive_report(dev_addr, instance) )
    {
        printf("Error: cannot request report\r\n");
    }
}
