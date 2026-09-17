cmake_minimum_required(VERSION 3.14)
project(IUSBTransport LANGUAGES CXX)

add_library(IUSBTransport INTERFACE)

target_include_directories(IUSBTransport INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
