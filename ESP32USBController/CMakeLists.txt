idf_component_register(
    SRCS "ESP32USBController.cpp"
    INCLUDE_DIRS "include"
    REQUIRES esp_common esp_system usb
)

target_link_libraries(${COMPONENT_LIB}
    PRIVATE
        IUSBTransport
)