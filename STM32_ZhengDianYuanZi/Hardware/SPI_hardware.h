#ifndef __SPI_HARDWARE_H
#define __SPI_HARDWARE_H
#include <stdint.h>

void SPI_hardware_init(void);
void SPI2_GPIO_Init(void);
void SPI_hardware_W_SS(uint8_t BitValue);

#endif
