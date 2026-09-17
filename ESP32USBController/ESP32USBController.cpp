#include "ESP32USBController.hpp"
#include "esp_log.h"
#include <cstring>

void ESP32USBController::out_callback(usb_transfer_t* transfer)
{
    ESP32USBController* self = static_cast<ESP32USBController*>(transfer->context);

    if (self != nullptr) { xSemaphoreGive(self->out_sem); }

    return;
}

int ESP32USBController::send(const uint8_t* data, size_t len)
{
    if (dev_hdl == NULL) { return ESP_ERR_INVALID_STATE; }
    if (xSemaphoreTake(out_sem, portMAX_DELAY) != pdTRUE) { return ESP_FAIL; }
    memcpy(out_transfer->data_buffer, data, len);

    out_transfer->device_handle    = dev_hdl;
    out_transfer->bEndpointAddress = EP_OUT;
    out_transfer->callback         = this->out_callback;
    out_transfer->context          = this;
    out_transfer->timeout_ms       = timeout_ms;

    out_transfer->num_bytes = len;

    esp_err_t err = usb_host_transfer_submit(out_transfer);

    if (err != ESP_OK) { ESP_LOGE("USB", "usb_host_transfer_submit failed: %s (0x%x)", esp_err_to_name(err), err); }
    else {
        ESP_LOGD("USB", "usb_host_transfer_submit OK");
    }

    return err;
}