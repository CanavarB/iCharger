#include "iCharger.hpp"

#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>

using namespace ICHARGER;

void iCharger::get_cell_voltage_from_log(uint16_t* cell_voltages)
{
    if (xSemaphoreTake(log_packet_10_mutex, portMAX_DELAY) == pdTRUE) {
        memcpy(cell_voltages, LOGPACKET10.cell_voltage, sizeof(uint16_t) * CELL_NUM_PER_CHANNEL);

        xSemaphoreGive(log_packet_10_mutex);
    }
}

void iCharger::get_cell_voltage_from_packet(U16* cell_voltages)
{
    if (xSemaphoreTake(packet_mutex, portMAX_DELAY) == pdTRUE) {
        memcpy(cell_voltages, PACKET + sizeof(header_response_t), sizeof(U16) * CELL_NUM_PER_CHANNEL);

        xSemaphoreGive(packet_mutex);
    }
}

void ICHARGER::iCharger::get_control_status_from_packet(U16* control_status)
{
    if (xSemaphoreTake(packet_mutex, portMAX_DELAY) == pdTRUE) {
        memcpy(control_status, PACKET + sizeof(header_response_t), sizeof(U16));

        xSemaphoreGive(packet_mutex);
    }
}

void iCharger::get_cell_capacity_from_packet(S32* cell_capacities)
{
    if (xSemaphoreTake(packet_mutex, portMAX_DELAY) == pdTRUE) {
        memcpy(cell_capacities, PACKET + sizeof(header_response_t), sizeof(S32) * CELL_NUM_PER_CHANNEL);

        xSemaphoreGive(packet_mutex);
    }
}

void iCharger::get_cell_balance_status_from_packet(U8* cell_balance_status)
{
    if (xSemaphoreTake(packet_mutex, portMAX_DELAY) == pdTRUE) {
        memcpy(cell_balance_status, PACKET + sizeof(header_response_t), sizeof(U8) * CELL_NUM_PER_CHANNEL);

        xSemaphoreGive(packet_mutex);
    }
}

void iCharger::get_run_status_from_packet(U16* run_status)
{
    if (xSemaphoreTake(packet_mutex, portMAX_DELAY) == pdTRUE) {
        memcpy(run_status, PACKET + sizeof(header_response_t), sizeof(U16));

        xSemaphoreGive(packet_mutex);
    }
}

void iCharger::get_statusword_from_packet(U16* statusword)
{
    if (xSemaphoreTake(packet_mutex, portMAX_DELAY) == pdTRUE) {
        memcpy(statusword, PACKET + sizeof(header_response_t), sizeof(U16));

        xSemaphoreGive(packet_mutex);
    }
}

int iCharger::send_get(U16 start_address, U16 count)
{
    modbus_adu_t buffer;

    memset(buffer.raw, 0, sizeof(buffer));

    buffer.header.lenght = 7;
    buffer.header.frame_type = frame_type_t::FRAME_TYPE;
    buffer.func_code = READ_INPUT_REGISTER_FUNC_CODE;
    buffer.start_address = __builtin_bswap16(start_address);
    buffer.count = __builtin_bswap16(count);

#if 0
    int actual = sizeof(buffer);

    std::cout << "\x1b[32mTX (" << actual << "): \x1b[0m\n";

    for (int i = 0; i < actual; i++)
    {
        std::cout << std::uppercase
                  << std::hex
                  << std::setw(2)
                  << std::setfill('0')
                  << static_cast<int>(buffer.raw[i])
                  << " ";
    }

    std::cout << std::dec << std::endl;
#endif

    return transport->send(buffer.raw, sizeof(buffer));
}

int ICHARGER::iCharger::send_set(U16 address, U16* value, U16 size)
{
    modbus_adu_t buffer;

    memset(buffer.raw, 0, sizeof(buffer));

    buffer.header.lenght = 8 + size * (sizeof(size) / sizeof(uint8_t));

    buffer.header.frame_type = frame_type_t::FRAME_TYPE;
    buffer.func_code = WRITE_MULTIPLE_HOLDING_REGISTER_FUNC_CODE;
    buffer.start_address = __builtin_bswap16(address);
    buffer.count = __builtin_bswap16(size);
    buffer.byte_count = size * (sizeof(size) / sizeof(uint8_t));

    for (size_t i = 0; i < size; i++) {
        buffer.data[i] = __builtin_bswap16(value[i]);
    }

#if 0
    int actual = sizeof(buffer);
    std::cout << "\x1b[32mTX (" << actual << "): \x1b[0m\n";

    for (int i = 0; i < actual; i++)
    {
        std::cout << std::uppercase
                  << std::hex
                  << std::setw(2)
                  << std::setfill('0')
                  << static_cast<int>(buffer.raw[i])
                  << " ";
    }
#endif

    std::cout << std::dec << std::endl;

    return transport->send(buffer.raw, sizeof(buffer));
}

int iCharger::send_get_run_status(channel_t channel)
{
    return send_get((channel == channel_t::CHANNEL_1) ? CHANNEL_1_RUN_STATUS_ADDRESS : CHANNEL_2_RUN_STATUS_ADDRESS,
                    sizeof(U16) / sizeof(U16));
}

int iCharger::send_set_order_lock(order_lock_t order_lock)
{
    U16 value = static_cast<U16>(order_lock);

    return send_set(ORDER_LOCK_ADDRESS, &value, 1);
}

int iCharger::send_set_order(order_t order)
{
    U16 value = static_cast<U16>(order);

    return send_set(ORDER_ADDRESS, &value, 1);
}

int iCharger::send_get_status_word() { return send_get(STATUSWORD_ADDRESS, sizeof(U16) / sizeof(U16)); }

int iCharger::send_set_control_register(control_registers_t* control_register)
{ return send_set(CONTROL_REGISTER_BASE_ADDRESS, reinterpret_cast<U16*>(control_register), 5); }

int iCharger::send_get_cell_voltage(channel_t channel)
{
    return send_get((channel == channel_t::CHANNEL_1) ? CHANNEL_1_CELL_VOLTAGE_ADDRESS : CHANNEL_2_CELL_VOLTAGE_ADDRESS,
                    CELL_NUM_PER_CHANNEL * sizeof(U16) / sizeof(U16));
}

int iCharger::send_get_control_status(channel_t channel)
{
    send_get((channel == channel_t::CHANNEL_1) ? CHANNEL_1_CONTROL_STATUS_ADDRESS : CHANNEL_2_CONTROL_STATUS_ADDRESS,
             sizeof(U16) / sizeof(U16));

    return 0;
}

int iCharger::send_get_cell_capacity(channel_t channel)
{
    return send_get((channel == channel_t::CHANNEL_1) ? CHANNEL_1_CELL_CAPACITY_ADDRESS
                                                      : CHANNEL_2_CELL_CAPACITY_ADDRESS,
                    CELL_NUM_PER_CHANNEL * sizeof(S32) / sizeof(U16));
}

int iCharger::send_get_cell_balance_status(channel_t channel)
{
    return send_get((channel == channel_t::CHANNEL_1) ? CHANNEL_1_CELL_BALANCE_STATUS_ADDRESS
                                                      : CHANNEL_2_CELL_BALANCE_STATUS_ADDRESS,
                    (CELL_NUM_PER_CHANNEL * sizeof(U8)) / sizeof(U16));
}

frame_type_t iCharger::parser(uint8_t* buffer)
{
    switch (reinterpret_cast<header_t*>(buffer)->frame_type) {
    case frame_type_t::FRAME_TYPE: {
        if (xSemaphoreTake(packet_mutex, portMAX_DELAY) == pdTRUE) {
            memcpy(PACKET, buffer, PACKET_SIZE);

            xSemaphoreGive(packet_mutex);
        }

        break;
    }

    case frame_type_t::FRAME_TYPE_LOG10: {
        if (xSemaphoreTake(log_packet_10_mutex, portMAX_DELAY) == pdTRUE) {
            memcpy(LOGPACKET10.raw, buffer, PACKET_SIZE);

            xSemaphoreGive(log_packet_10_mutex);
        }

        break;
    }

    case frame_type_t::FRAME_TYPE_LOG11:
    case frame_type_t::FRAME_TYPE_LOG20:
    default:
        break;
    }

    return reinterpret_cast<header_t*>(buffer)->frame_type;
}

iCharger::~iCharger()
{
    if (packet_mutex != nullptr) vSemaphoreDelete(packet_mutex);

    if (log_packet_10_mutex != nullptr) vSemaphoreDelete(log_packet_10_mutex);
}
