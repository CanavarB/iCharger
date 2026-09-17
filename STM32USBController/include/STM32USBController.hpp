#include "IUSBTransport.hpp"

#include "usbh_core.h"
#include "usbh_hid.h"

class STM32USBController : IUSBTransport {
  private:
    USBH_HandleTypeDef* host;

  public:
    explicit STM32USBController(USBH_HandleTypeDef* host) : host(host) {}
    int send(const uint8_t* data, size_t len) override;
    ~STM32USBController() = default;
};