#include "My_DMA.h"
#include "includes.h"
DMA_Parameter_t DMA_Parameter;



void My_DMA_init(void)
{
	
	
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	DMA_InitTypeDef DMA_InitStructure;



	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;//外设站点地址
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//传输的数据大小 字节 半字 字
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//地址自增
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADC_paramater.ADC_list;//存储器站点
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//数据大小
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//地址自增
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;//传输方向 DMA_DIR_PeripheralSRC:外设->存储器  or  DMA_DIR_PeripheralDST:存储器->外设   
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;	//优先级
	DMA_InitStructure.DMA_BufferSize = ADC_LIST_LENGTH;//数组大小

	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//enable:软件触发 disable:硬件触发

	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;//dma转运模式 是否自动重装 circular：自动重装 normal:不重装

	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	
	DMA_Cmd(DMA1_Channel1, ENABLE);


}


void MyDMA_Transfer(void)
{
	DMA_Cmd(DMA1_Channel1, DISABLE);
	DMA_SetCurrDataCounter(DMA1_Channel1, DMA_Parameter.MyDMA_Size);
	DMA_Cmd(DMA1_Channel1, ENABLE);
	
	while(DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);
	DMA_ClearFlag(DMA1_FLAG_TC1);

}