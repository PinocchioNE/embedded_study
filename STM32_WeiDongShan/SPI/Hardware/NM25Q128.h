#ifndef __NM25Q128_H
#define __NM25Q128_H

#include <stdint.h>

#define NM25Q128_CMD_READ_DATA          0x03
#define NM25Q128_CMD_READ_JEDEC_ID      0x9F
#define NM25Q128_CMD_READ_MANUFACTURER_ID      0x90


void NM25Q128_Init(void);
void NM25Q128_ReadID(uint8_t *MID, uint16_t *DID, uint16_t order);
void spi_data_init(void);
uint8_t NM25Q128_SPI2_read_write_byte(uint8_t tx_data);
#endif
