#include "IUSBTransport/IUSBTransport.hpp"
#include "usb/usb_host.h"
#include "usb/usb_types_stack.h"

constexpr uint8_t EP_OUT = 0x01;

class ESP32USBController : public IUSBTransport {
  private:
    uint32_t timeout_ms;
    SemaphoreHandle_t out_sem;

  public:
    usb_transfer_t* out_transfer;
    usb_device_handle_t dev_hdl;

    ESP32USBController(uint32_t timeout_ms) : timeout_ms(timeout_ms)
    {
        out_sem = xSemaphoreCreateBinary();
        xSemaphoreGive(out_sem);
    };

    int send(const uint8_t* data, size_t len) override;
    void set_dev_handle(usb_device_handle_t dev_hdl);
    static void out_callback(usb_transfer_t* transfer);

    ~ESP32USBController() = default;
};
