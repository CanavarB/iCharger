#pragma once
#include <cstdint>
#include <cstddef>

class IUSBTransport {
  public:
    virtual ~IUSBTransport() = default;

    virtual int send(const uint8_t* data, size_t len) = 0;
};