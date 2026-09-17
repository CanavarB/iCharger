#pragma once

#define MODEL_S6 1
#define MODEL_X6 2
#define MODEL_DX6 3
#define MODEL_X8 4
#define MODEL_DX8 5
#define MODEL_X12 6
#define MODEL_DX12 7

#define ICHARGER_MODEL MODEL_X6

#if ICHARGER_MODEL == MODEL_S6 || ICHARGER_MODEL == MODEL_X6 || ICHARGER_MODEL == MODEL_DX6
#define CELL_NUM_PER_CHANNEL 6
#elif ICHARGER_MODEL == MODEL_DX8 || ICHARGER_MODEL == MODEL_X8
#define CELL_NUM_PER_CHANNEL 8
#elif ICHARGER_MODEL == MODEL_DX12 || ICHARGER_MODEL == MODEL_X12
#define CELL_NUM_PER_CHANNEL 12
#endif

#if ICHARGER_MODEL == MODEL_DX6 || ICHARGER_MODEL == MODEL_DX8 || ICHARGER_MODEL == MODEL_DX12
#define ICHARGER_CHANNEL_NUM 2
#else
#define ICHARGER_CHANNEL_NUM 1
#endif

namespace ICHARGER {

constexpr uint8_t PACKET_SIZE = 64;
constexpr uint8_t MAX_WRITE_REGISTERS = 28;
constexpr uint8_t READ_HOLDING_REGISTER_FUNC_CODE = 0x03;
constexpr uint8_t READ_INPUT_REGISTER_FUNC_CODE = 0x04;
constexpr uint8_t WRITE_MULTIPLE_HOLDING_REGISTER_FUNC_CODE = 0x10;

enum class channel_t : uint8_t {
    CHANNEL_1,
#if ICHARGER_CHANNEL_NUM == 2
    CHANNEL_2,
#endif
    CHANNEL_MAX
};

enum class frame_type_t : uint8_t {
    FRAME_TYPE_LOG10 = 0x10,
    FRAME_TYPE_LOG11 = 0x11,
    FRAME_TYPE_LOG20 = 0x20,
    FRAME_TYPE = 0x30
};

typedef uint32_t U32;
typedef int32_t S32;
typedef uint16_t U16;
typedef int16_t S16;
typedef uint8_t U8;
typedef int8_t S8;

enum {
    DEVICE_ONLY_READS_MESSAGE_BASE_ADDRESS,
    DEVICE_ID_ADDRESS = DEVICE_ONLY_READS_MESSAGE_BASE_ADDRESS,
    DEVICE_SN_ADDRESS,
    SOFTWARE_VERSION_ADDRESS = DEVICE_ID_ADDRESS + 7,
    HARDWARE_VERSION_ADDRESS,
    SYSTEM_LENGHT_ADDRESS,
    MEMORY_LENGHT_ADDRESS,
    STATUSWORD_ADDRESS,
    CHANNEL_1_INPUT_READ_ONLY_BASE_ADDRESS = 0x0100,
    CHANNEL_1_TIMESTAMP_ADDRESS = CHANNEL_1_INPUT_READ_ONLY_BASE_ADDRESS,
    CHANNEL_1_CURRENT_OUTPUT_POWER_ADDRESS = CHANNEL_1_INPUT_READ_ONLY_BASE_ADDRESS + 2,
    CHANNEL_1_CURRENT_OUTPUT_CURRENT_ADDRESS = CHANNEL_1_INPUT_READ_ONLY_BASE_ADDRESS + 4,
    CHANNEL_1_CURRENT_INPUT_VOLTAGE_ADDRESS,
    CHANNEL_1_CURRENT_OUTPUT_VOLTAGE_ADDRESS,
    CHANNEL_1_CURRENT_OUTPUT_CAPACITY_ADDRESS,
    CHANNEL_1_CURRENT_INTERNAL_TEMPERATURE_ADDRESS = CHANNEL_1_INPUT_READ_ONLY_BASE_ADDRESS + 9,
    CHANNEL_1_CURRENT_EXTERNAL_TEMPERATURE_ADDRESS,
    CHANNEL_1_CELL_VOLTAGE_ADDRESS,
    CHANNEL_1_CELL_BALANCE_STATUS_ADDRESS = CHANNEL_1_INPUT_READ_ONLY_BASE_ADDRESS + 27,
    CHANNEL_1_CELL_INTERNAL_RESISTANCE_ADDRESS = CHANNEL_1_INPUT_READ_ONLY_BASE_ADDRESS + 35,
    CHANNEL_1_CELLS_TOTAL_INTERNAL_RESISTANCE_ADDRESS = CHANNEL_1_INPUT_READ_ONLY_BASE_ADDRESS + 51,
    CHANNEL_1_LINE_INTERNAL_ADDRESS,
    CHANNEL_1_CYCLES_COUNT_ADDRESS,
    CHANNEL_1_CONTROL_STATUS_ADDRESS,
    CHANNEL_1_RUN_STATUS_ADDRESS,
    CHANNEL_1_RUN_ERROR_ADDRESS,
    CHANNEL_1_DIALOG_BOX_ID_ADDRESS,
    CHANNEL_1_CELL_CAPACITY_ADDRESS,
    CHANNEL_2_INPUT_READ_ONLY_BASE_ADDRESS = 0x0200,
    CHANNEL_2_TIMESTAMP_ADDRESS = CHANNEL_2_INPUT_READ_ONLY_BASE_ADDRESS,
    CHANNEL_2_CURRENT_OUTPUT_POWER_ADDRESS = CHANNEL_2_INPUT_READ_ONLY_BASE_ADDRESS + 2,
    CHANNEL_2_CURRENT_OUTPUT_CURRENT_ADDRESS = CHANNEL_2_INPUT_READ_ONLY_BASE_ADDRESS + 4,
    CHANNEL_2_CURRENT_INPUT_VOLTAGE_ADDRESS,
    CHANNEL_2_CURRENT_OUTPUT_VOLTAGE_ADDRESS,
    CHANNEL_2_CURRENT_OUTPUT_CAPACITY_ADDRESS,
    CHANNEL_2_CURRENT_INTERNAL_TEMPERATURE_ADDRESS = CHANNEL_2_INPUT_READ_ONLY_BASE_ADDRESS + 9,
    CHANNEL_2_CURRENT_EXTERNAL_TEMPERATURE_ADDRESS,
    CHANNEL_2_CELL_VOLTAGE_ADDRESS,
    CHANNEL_2_CELL_BALANCE_STATUS_ADDRESS = CHANNEL_2_INPUT_READ_ONLY_BASE_ADDRESS + 27,
    CHANNEL_2_CELL_INTERNAL_RESISTANCE_ADDRESS = CHANNEL_2_INPUT_READ_ONLY_BASE_ADDRESS + 35,
    CHANNEL_2_CELLS_TOTAL_INTERNAL_RESISTANCE_ADDRESS = CHANNEL_2_INPUT_READ_ONLY_BASE_ADDRESS + 51,
    CHANNEL_2_LINE_INTERNAL_ADDRESS,
    CHANNEL_2_CYCLES_COUNT_ADDRESS,
    CHANNEL_2_CONTROL_STATUS_ADDRESS,
    CHANNEL_2_RUN_STATUS_ADDRESS,
    CHANNEL_2_RUN_ERROR_ADDRESS,
    CHANNEL_2_DIALOG_BOX_ID_ADDRESS,
    CHANNEL_2_CELL_CAPACITY_ADDRESS,
    CONTROL_REGISTER_BASE_ADDRESS = 0x8000,
    SELECT_RUN_OPERATION_ADDRESS = CONTROL_REGISTER_BASE_ADDRESS,
    SELECT_MEMORY_ADDRESS,
    SELECT_CHANNEL_ADDRESS,
    ORDER_LOCK_ADDRESS,
    ORDER_ADDRESS,
    LIMIT_CURRENT_ADDRESS,
    LIMIT_VOLTAGE_ADDRESS,
    SYSTEM_STORAGE_AREA_BASE_ADDRESS = 0x8400,
    MEMORY_INDEX_STORAGE_AREA_BASE_ADDRESS = 0x8800,
    MEMORY_STORAGE_AREA_BASE_ADDRESS = 0x8C00,
};

enum class order_t : U16 {
    ORDER_STOP,
    ORDER_RUN,
    ORDER_MODIFY,
    ORDER_WRITE_SYS,
    ORDER_WRITE_MEM_HEAD,
    ORDER_WRITE_MEM,
    ORDER_TRANS_LOG_ON,
    ORDER_TRANS_LOG_OFF,
    ORDER_MSGBOX_YES,
    ORDER_MSGBOX_NO,
    ORDER_MAX
};

enum class operation_t : U16 {
    OPERATION_CHARGE,
    OPERATION_STORAGE,
    OPERATION_DISCHARGE,
    OPERATION_CYCLE,
    OPERATION_BALANCE,
    OPERATION_POWER,
    OPERATION_MAX
};

enum class order_lock_t : U16 {
    ORDER_LOCK,
    ORDER_UNLOCK = 0x55AA
};

enum class memory_t : U16 {
    LIPO,
    LILO,
    LIFE,
    LIHV,
    LTO,
    NIMH,
    NICD,
    NIZN,
    PB,
    POWER,
    USER,
    MEMORY_MAX
};

typedef union {
    struct __attribute__((packed)) {
        uint8_t lenght;
        frame_type_t frame_type;
    };
    uint8_t raw[2];
} header_t;

typedef union {
    struct __attribute__((packed)) {
        header_t header;
        uint8_t byte_lenght;
    };
    uint8_t raw[3];
} header_response_t;

typedef union {
    struct __attribute__((packed)) {
        header_t header;
        uint8_t func_code;
        uint16_t start_address;
        uint16_t count;
        uint8_t byte_count;
        uint16_t data[MAX_WRITE_REGISTERS];
    };
    uint8_t raw[PACKET_SIZE];
} modbus_adu_t;

typedef union {
    struct {
        uint8_t length;
        frame_type_t frame_type;
        uint8_t channel;
        uint32_t tick;

        uint8_t status;
        uint8_t state;

        uint16_t field1;
        uint16_t field2;

        uint32_t field3;
        uint32_t field4;
        uint16_t cell_voltage[CELL_NUM_PER_CHANNEL];
    };
    uint8_t raw[PACKET_SIZE];
} LogPacket10_t;

typedef union {
    struct {
        U16 device_id;
        S8 device_sn[12];
        U16 software_version;
        U16 hardware_version;
        U16 system_length;
        U16 memory_length;
        U16 status_word;
    };
    uint8_t raw[64];
} device_only_read_message_t;

typedef union {
    struct __attribute__((packed)) {
        operation_t operation;
        memory_t memory;
        channel_t channel;
        order_lock_t order_lock;
        order_t order;
        U16 limit_current;
        U16 limit_voltage;
    };
    uint8_t raw[14];
} control_registers_t;

typedef union __attribute__((packed)) {
    struct {
        U32 timestamp;
        U32 output_power;
        S16 output_current;
        U16 input_voltage;
        U16 output_voltage;
        S32 output_capacity;
        S16 internal_temp;
        S16 external_temp;

        U16 cell_voltage_raw[CELL_NUM_PER_CHANNEL];
        U8 cell_balance_status[CELL_NUM_PER_CHANNEL];
        U16 cell_internal_resistance[CELL_NUM_PER_CHANNEL];
    };
    uint8_t* raw;
} dx12_live_data_t;

} // namespace ICHARGER