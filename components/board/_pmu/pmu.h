#pragma once

#include "freertos/FreeRTOS.h"
#include "axp192.h"

void Core2ForAWS_PMU_Init(uint16_t ldo2_volt, uint16_t ldo3_volt, uint16_t dc2_volt, uint16_t dc3_volt);
void Core2ForAWS_PMU_SetPowerIn(uint8_t mode);
float Core2ForAWS_PMU_GetBatVolt(void);
float Core2ForAWS_PMU_GetBatCurrent(void);