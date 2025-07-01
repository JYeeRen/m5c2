/**
 * @file disp_driver.h
 */

#ifndef DISP_DRIVER_H
#define DISP_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "lvgl.h"

#include "ili9341.h"


/*********************
 *      DEFINES
 *********************/
#define DISP_BUF_SIZE  (320 * 32)  // ILI9341 屏幕宽度为 320 像素

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/* Initialize display */
void disp_driver_init(void);

/* Display flush callback */
void disp_driver_flush(lv_display_t * disp, const lv_area_t * area, uint8_t * px_map);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*DISP_DRIVER_H*/
