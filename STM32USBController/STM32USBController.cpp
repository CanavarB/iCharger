#include "../include/STM32USBController.hpp"
#define HID_REPORT_OUTPUT 0x02

int STM32USBController::send(const uint8_t* data, size_t len)
{
    if (host == nullptr) { return -1; }

    if (data == nullptr || len == 0) { return -2; }

    if (host->gState != HOST_CLASS) { return -3; }

    if (len > UINT16_MAX) { return -4; }

    USBH_StatusTypeDef status =
        USBH_HID_SetReport(host, HID_REPORT_OUTPUT, 0, const_cast<uint8_t*>(data), static_cast<uint16_t>(len));

    if (status != USBH_OK) { return -5; }

    return static_cast<int>(len);
}
