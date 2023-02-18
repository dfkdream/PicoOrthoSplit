add_executable(key_test main.cpp ../../key_matrix/KeyMatrix.cpp)
pico_enable_stdio_usb(key_test 1)
target_link_libraries(key_test pico_stdlib)
pico_add_extra_outputs(key_test)