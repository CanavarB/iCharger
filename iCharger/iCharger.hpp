#pragma once

#include "IUSBTransport/IUSBTransport.hpp"
#include "freertos/FreeRTOS.h"
#include "iCharger.h"
#include <stdint.h>

namespace ICHARGER {

class iCharger {
  private:
    IUSBTransport* transport;
    SemaphoreHandle_t packet_mutex;
    uint8_t PACKET[PACKET_SIZE];
    SemaphoreHandle_t log_packet_10_mutex;
    LogPacket10_t LOGPACKET10;

  public:
    iCharger(IUSBTransport* transport) : transport(transport)
    {
        packet_mutex = xSemaphoreCreateMutex();
        log_packet_10_mutex = xSemaphoreCreateMutex();
    };

    void get_cell_voltage_from_log(U16* cell_voltages);
    void get_cell_voltage_from_packet(U16* cell_voltages);
    void get_control_status_from_packet(U16* control_status);
    void get_cell_capacity_from_packet(S32* cell_capacities);
    void get_cell_balance_status_from_packet(U8* cell_balance_status);
    void get_statusword_from_packet(U16* statusword);
    void get_run_status_from_packet(U16* run_status);

    frame_type_t parser(uint8_t* buffer);

    int send_get(U16 start_address = 0, U16 count = 0);
    int send_set(U16 address, U16* value, U16 size = 1);
    int send_get_run_status(channel_t channel = channel_t::CHANNEL_1);
    int send_get_control_status(channel_t channel = channel_t::CHANNEL_1);
    int send_get_status_word();
    int send_get_cell_voltage(channel_t channel = channel_t::CHANNEL_1);
    int send_get_cell_capacity(channel_t channel = channel_t::CHANNEL_1);
    int send_get_cell_balance_status(channel_t channel = channel_t::CHANNEL_1);
    int send_set_order_lock(order_lock_t order_lock);
    int send_set_order(order_t order);
    // int send_set_control_register(operation_t operation, memory_t memory, channel_t channel,
    //                               order_lock_t order_lock = order_lock_t::ORDER_LOCK,
    //                               order_t order = order_t::ORDER_STOP, U16 limit_current = 0, U16 limit_voltage = 0);
    int send_set_control_register(control_registers_t* control_register);
    ~iCharger();
};

#define DX12_OP_ENABLE_CHARGE (1U << 0)
#define DX12_OP_ENABLE_STORAGE (1U << 2)
#define DX12_OP_ENABLE_DISCHARGE (1U << 3)
#define DX12_OP_ENABLE_CYCLE (1U << 4)
#define DX12_OP_ENABLE_BALANCE (1U << 5)
} // namespace ICHARGER
