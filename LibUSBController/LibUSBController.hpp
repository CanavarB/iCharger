#include "IUSBTransport/IUSBTransport.hpp"
#include <iostream>
#include <libusb-1.0/libusb.h>

namespace LIBUSBCONTROLLER {

constexpr uint16_t VID = 0x0483;
constexpr uint16_t PID = 0x5751;
constexpr uint8_t INTERFACE = 0;
constexpr uint8_t EP_IN = 0x81;
constexpr uint8_t EP_OUT = 0x01;

class LibUSBController : public IUSBTransport {
  private:
  public:
    libusb_device_handle* dev;
    libusb_transfer* transfer;
    libusb_context* ctx = nullptr;
    LibUSBController();
    int init();
    int send(const uint8_t* data, size_t len) override;

    ~LibUSBController();
};

LibUSBController::LibUSBController() {}

int LibUSBController::init()
{
    if (libusb_init(&ctx) != LIBUSB_SUCCESS) {
        std::cerr << "libusb_init failed\n";
        return -1;
    }
    dev = libusb_open_device_with_vid_pid(ctx, VID, PID);
    if (!dev) {
        std::cerr << "Device not found\n";
        libusb_exit(ctx);
        return -1;
    }
    if (libusb_kernel_driver_active(dev, INTERFACE) == 1) libusb_detach_kernel_driver(dev, INTERFACE);
    int ret = libusb_claim_interface(dev, INTERFACE);
    if (ret != LIBUSB_SUCCESS) {
        std::cerr << "Claim failed: " << libusb_error_name(ret) << std::endl;

        libusb_close(dev);
        libusb_exit(ctx);
        return -1;
    }
    std::cout << "Connected." << std::endl;

    transfer = libusb_alloc_transfer(0);
    return 0;
}

int LibUSBController::send(const uint8_t* data, size_t len)
{ return libusb_interrupt_transfer(dev, EP_OUT, const_cast<unsigned char*>(data), len, NULL, 1000); }

LibUSBController::~LibUSBController()
{
    std::cerr << "Cleaning up USB controller..." << std::endl;
    if (transfer) {
        libusb_cancel_transfer(transfer);
        libusb_free_transfer(transfer);
    }
    std::cerr << "Closing USB controller..." << std::endl;
    if (dev) {
        libusb_release_interface(dev, INTERFACE);
        libusb_close(dev);
    }
    std::cerr << "Exiting libusb..." << std::endl;
}
} // namespace LIBUSBCONTROLLER