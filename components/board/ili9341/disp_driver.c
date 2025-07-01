/**
 * @file disp_driver.c
 */

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>

#include "disp_driver.h"
#include "disp_spi.h"

#include "lvgl.h"

void disp_driver_init(void) {
    ili9341_init();
}

void disp_driver_flush(lv_display_t * disp, const lv_area_t * area, uint8_t * px_map) {
    ili9341_flush(disp, area, px_map);
}

