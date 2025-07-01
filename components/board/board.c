#include "stdbool.h"
#include <stdio.h>

#include "freertos/FreeRTOS.h"

#include "i2c_device.h"

#include "axp192.h"
#include "_pmu/pmu.h"
#include "_motor/motor.h"

#include "board.h"
#include "disp_driver.h"
#include "lvgl.h"
#include "disp_spi.h"
#include "ili9341.h"

// 工作时 green led 常亮
// 充电时 green led 闪烁
// 长按关机

void Core2ForAWS_LED_Enable(uint8_t enable)
{
    uint8_t value = enable ? 0 : 1;
    Axp192_SetGPIO1Mode(value);
}

void init_board(void)
{

    spi_mutex = xSemaphoreCreateMutex();

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

    // mode 0 lebel 0 -> 低电平
    // mode 0 lebel 1 -> 高电平
    // mode 1 lebel 0 -> 高电平
    // mode 1 lebel 1 -> 高电平
    printf("gpio1 mode: %d\n", Axp192_GetGpio1Mode());
    printf("gpio1 level: %d\n", Axp192_GetGpio1Level());

    printf("test charging led\n");
    printf("charging: %d\n", Axp192_GetChargeStatus());

    printf("test lcd\n");
    spi_bus_config_t bus_cfg = {
        .mosi_io_num = 23,
        .miso_io_num = 38,
        .sclk_io_num = 18,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 320 * 32 * 3,
    };
    spi_bus_initialize(SPI_HOST_USE, &bus_cfg, SPI_DMA_CHAN);

    // xSemaphoreTake(xGuiSemaphore, portMAX_DELAY);
    // lv_init();

    disp_spi_add_device(SPI_HOST_USE);
    disp_driver_init();

    // spi_device_acquire_bus(SPI_HOST_USE, portMAX_DELAY);
    // ili9341_send_cmd(0x0C);
    // // 创建并设置绿色背景
    // lv_obj_t *scr = lv_scr_act();
    // if (scr == NULL)
    // {
    //     printf("LVGL 屏幕对象获取失败，请检查 LVGL 初始化！\n");
    // }
    // else
    // {
    //     lv_obj_set_style_bg_color(scr, lv_color_make(0, 255, 0), LV_PART_MAIN);
    // }
}
