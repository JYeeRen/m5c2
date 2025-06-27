#include "freertos/FreeRTOS.h"
#include "axp192.h"
#include "pmu.h"

float Core2ForAWS_PMU_GetBatVolt(void) {
    return Axp192_GetBatVolt();
}

float Core2ForAWS_PMU_GetBatCurrent(void) {
    return Axp192_GetBatCurrent();
}

void Core2ForAWS_PMU_SetPowerIn(uint8_t mode) {
    if (mode) {
        Axp192_SetGPIO0Mode(0);
        Axp192_EnableExten(0);
    } else {
        Axp192_EnableExten(1);
        Axp192_SetGPIO0Mode(1);
    }
}

void Core2ForAWS_PMU_Init(uint16_t ldo2_volt, uint16_t ldo3_volt, uint16_t dc2_volt, uint16_t dc3_volt) {
    uint8_t value = 0x00;
    value |= (ldo2_volt > 0) << AXP192_LDO2_EN_BIT;
    value |= (ldo3_volt > 0) << AXP192_LDO3_EN_BIT;
    value |= (dc2_volt > 0) << AXP192_DC2_EN_BIT;
    value |= (dc3_volt > 0) << AXP192_DC3_EN_BIT;
    value |= 0x01 << AXP192_DC1_EN_BIT;

    Axp192_Init();

    // value |= 0x01 << AXP192_EXT_EN_BIT;
    Axp192_SetLDO23Volt(ldo2_volt, ldo3_volt);
    // Axp192_SetDCDC1Volt(3300);
    Axp192_SetDCDC2Volt(dc2_volt);
    Axp192_SetDCDC3Volt(dc3_volt);
    Axp192_SetVoffVolt(3000);
    Axp192_SetChargeCurrent(CHARGE_Current_100mA);
    Axp192_SetChargeVoltage(CHARGE_VOLT_4200mV);
    Axp192_EnableCharge(1);
    Axp192_SetPressStartupTime(STARTUP_128mS);
    Axp192_SetPressPoweroffTime(POWEROFF_4S);
    Axp192_EnableLDODCExt(value);
    Axp192_SetGPIO4Mode(1);
    Axp192_SetGPIO2Mode(1);
    Axp192_SetGPIO2Level(0);

    Axp192_SetGPIO0Volt(3300);
    Axp192_SetAdc1Enable(0xfe);
    Axp192_SetGPIO1Mode(1);
    Core2ForAWS_PMU_SetPowerIn(0);
}
