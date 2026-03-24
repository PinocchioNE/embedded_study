#ifndef __SPI_SOFTWARE_H
#define __SPI_SOFTWARE_H

#include <stdint.h>




void SPI_software_Init(void);
void SPI_software_Start(void);
void SPI_software_Stop(void);
uint8_t SPI_software_SwapByte_MaskOffCode(uint8_t ByteSend);
uint8_t SPI_software_SwapByte_GressionCode(uint8_t ByteSend);


#endif
