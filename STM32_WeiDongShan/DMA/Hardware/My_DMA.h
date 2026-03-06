#ifndef __MY_DMA_H
#define __MY_DMA_H

#include <stdint.h>


typedef struct
{
	uint8_t DATA_A[4];
	uint8_t DATA_B[4];
	uint16_t MyDMA_Size;
	
}DMA_Parameter_t;
extern DMA_Parameter_t DMA_Parameter;


void MyDMA_Transfer(void);
void My_DMA_init(uint32_t AddrA, uint32_t AddrB, uint16_t size);

#endif