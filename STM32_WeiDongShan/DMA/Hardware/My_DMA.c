#include "stm32f10x.h"
#include "My_DMA.h"



void My_DMA_init(uint32_t AddrA, uint32_t AddrB, uint16_t size)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	DMA_InitTypeDef DMA_InitStructure;
	
	DMA_InitStructure.DMA_PeripheralBaseAddr = AddrA;//外设站点地址
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//传输的数据大小 字节 半字 字
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;//地址自增
	DMA_InitStructure.DMA_MemoryBaseAddr = AddrB;//存储器站点
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//数据大小
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//地址自增
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;//传输方向 DMA_DIR_PeripheralSRC:外设->存储器  or  DMA_DIR_PeripheralDST:存储器->外设   
	DMA_InitStructure.DMA_Priority = ;	
	DMA_InitStructure.DMA_BufferSize = size;//数组大小

	DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;//enable:软件触发 disable:硬件触发

	DMA_InitStructure.DMA_Mode = ;

	


}