cmake_minimum_required(VERSION 3.12)

include(pico-sdk/pico_sdk_init.cmake)

project(OrthoSplit C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

pico_sdk_init()

set(PICO_PIO_USB_DIR "Pico-PIO-USB")
add_subdirectory(${PICO_PIO_USB_DIR} pico_pio_usb)

add_executable(OrthoSplit main.cpp
        keyboard/keyboard.cpp
        key_matrix/KeyMatrix.cpp
        layer_handler/LayerHandler.cpp layer_handler/LayerHandler.h
        key_handlers/KeyHandlerFactory.cpp key_handlers/KeyHandlerFactory.h
        key_handlers/KeyHandlers.cpp key_handlers/KeyHandlers.h
        hid_host/HIDHost.cpp hid_host/HIDHost.h)

target_sources(OrthoSplit PRIVATE
        main.cpp
        usb/usb_descriptors.c
        ${PICO_TINYUSB_PATH}/src/portable/raspberrypi/pio_usb/dcd_pio_usb.c
        ${PICO_TINYUSB_PATH}/src/portable/raspberrypi/pio_usb/hcd_pio_usb.c
        )

target_include_directories(OrthoSplit PRIVATE usb)

target_compile_definitions(OrthoSplit PRIVATE PIO_USB_USE_TINYUSB)

target_link_libraries(OrthoSplit pico_stdlib tinyusb_device pico_pio_usb tinyusb_host pico_multicore)
pico_add_extra_outputs(OrthoSplit)

add_subdirectory(tools)