#include "freertos/FreeRTOS.h"
#include "axp192.h"
#include "motor.h"

void Core2ForAWS_Motor_SetStrength(uint8_t strength) {
    if (strength > 100) {
        strength = 100;
    }

    if (strength > 0){
        uint16_t volt = (uint32_t)strength * (AXP192_LDO_VOLT_MAX - AXP192_LDO_VOLT_MIN) / 100 + AXP192_LDO_VOLT_MIN;
        Axp192_SetLDO3Volt(volt);
        Axp192_EnableLDO3(1);
    } else {
        Axp192_EnableLDO3(0);
    }
}