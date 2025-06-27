#include "stdbool.h"
#include <stdio.h>

#include "freertos/FreeRTOS.h"

#include "i2c_device.h"

#include "axp192.h"
#include "_pmu/pmu.h"
#include "_motor/motor.h"

#include "board.h"

void Core2ForAWS_LED_Enable(uint8_t enable) {
    uint8_t value = enable ? 0 : 1;
    Axp192_SetGPIO1Mode(value);
}

void init_board(void)
{
    printf("init board\n");

    printf("init pmu\n");
    // AXP_IO0 -> BUS_PW_EN
    // AXP_IO1 -> SYS LED
    // AXP_IO2 -> SPK EN
    // AXP_IO3 -> no use
    // AXP_IO4 -> LCD RST
    // 
    // LDO1_volt RTC VDD -> 
    // LDO2_volt PERI VDD -> 3.3V -> LCD VDD -> 屏幕
    // LDO3_volt VIB MOTOR -> 3.3V -> 马达
    // 
    // dc2_volt 
    // dc3_volt
    Core2ForAWS_PMU_Init(3300, 0, 0, 2700);

    printf("light green led\n");
    Axp192_SetGPIO1Mode(0);
    Axp192_SetGPIO1Level(0);
    Core2ForAWS_LED_Enable(1);

    printf("test motor\n");
    Core2ForAWS_Motor_SetStrength(100);
    vTaskDelay(300 / portTICK_PERIOD_MS);
    Core2ForAWS_Motor_SetStrength(0);

    // printf("test pwr led\n");
    // printf("gpio1 mode: %d\n", Axp192_GetGpio1Mode());
    // printf("gpio1 level: %d\n", Axp192_GetGpio1Level());

    // vTaskDelay(2000 / portTICK_PERIOD_MS);
    // mode 0 lebel 0 -> 低电平
    // mode 0 lebel 1 -> 高电平
    // mode 1 lebel 0 -> 高电平
    // mode 1 lebel 1 -> 高电平
    printf("gpio1 mode: %d\n", Axp192_GetGpio1Mode());
    printf("gpio1 level: %d\n", Axp192_GetGpio1Level());

    // vTaskDelay(2000 / portTICK_PERIOD_MS);
    // Axp192_SetGPIO1Mode(0);
    // Axp192_SetGPIO1Level(0);
    // printf("gpio1 mode: %d\n", Axp192_GetGpio1Mode());
    // printf("gpio1 level: %d\n", Axp192_GetGpio1Level());

    //     vTaskDelay(2000 / portTICK_PERIOD_MS);
    // Axp192_SetGPIO1Mode(1);
    // Axp192_SetGPIO1Level(1);
    // printf("gpio1 mode: %d\n", Axp192_GetGpio1Mode());
    // printf("gpio1 level: %d\n", Axp192_GetGpio1Level());
}
