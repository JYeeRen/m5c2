#pragma once

#include "axp192.h"
#include "i2c_device.h"

void init_board(void);

#define SPI_HOST_USE HSPI_HOST
#define SPI_DMA_CHAN 2