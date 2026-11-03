
cmake_minimum_required(VERSION 3.13)

# Import the Raspberry Pi Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Define project
project(hello_pico C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the Pico SDK
pico_sdk_init()

# Create executable
add_executable(hello_pico main.c)

# Link Pico standard library
target_link_libraries(hello_pico pico_stdlib)

# Enable USB serial output
pico_enable_stdio_usb(hello_pico 1)

# Disable UART output
pico_enable_stdio_uart(hello_pico 0)

# Generate UF2, BIN and other output files
pico_add_extra_outputs(hello_pico)
