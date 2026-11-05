# BUILD FOR MAC
# cmake -S . -B build-mac -DBUILD_FOR_PICO=OFF
# cmake --build build-mac
# BUILD FOR PICO
# or cmake -S . -B build-pico -DBUILD_FOR_PICO=ON -DPICO_BOARD=pico2_w
# cmake --build build-pico

cmake_minimum_required(VERSION 3.13)

option(BUILD_FOR_PICO "Build for Raspberry Pi Pico" ON)

if(BUILD_FOR_PICO)
    include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
endif()

project(calc C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(CALC_SOURCES
    main.c
    include/calc.c
    include/calc_output.c
    include/calc_input.c
)

if(BUILD_FOR_PICO)

    pico_sdk_init()

    add_executable(calc ${CALC_SOURCES})

    target_link_libraries(calc pico_stdlib)

    pico_enable_stdio_usb(calc 1)
    pico_enable_stdio_uart(calc 0)

    pico_add_extra_outputs(calc)

else()

    add_executable(calc ${CALC_SOURCES})

endif()