cmake_minimum_required(VERSION 3.14)
project(STM32USBController LANGUAGES CXX)

add_library(STM32USBController STATIC
    STM32USBController.cpp
)

target_include_directories(STM32USBController PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(STM32USBController PUBLIC IUSBTransport)
