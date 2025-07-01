/**
 * @file lv_templ.h
 *
 */

#ifndef ILI9341_H
#define ILI9341_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdbool.h>

#include "lvgl.h"

/*********************
 *      DEFINES
 *********************/
#define ILI9341_DC   15

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void ili9341_init(void);
void ili9341_flush(lv_display_t * disp, const lv_area_t * area, uint8_t * px_map);
void ili9341_sleep_in(void);
void ili9341_sleep_out(void);

/**********************
 *      MACROS
 **********************/


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*ILI9341_H*/
