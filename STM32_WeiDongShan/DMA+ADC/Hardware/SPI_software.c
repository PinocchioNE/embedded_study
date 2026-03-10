#include "stm32f10x.h"
#include "SPI_software.h"
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdarg.h>



void SPI_software_W_SS(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_9, (BitAction)BitValue);
}

void SPI_software_W_SCK(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_5, (BitAction)BitValue);
}

void SPI_software_W_MOSI(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_7, (BitAction)BitValue);
}

uint8_t SPI_software_R_MISO(void)
{
	return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);
}





void SPI_software_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //  CC 
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	

 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7; //  SCK MOSI
 	GPIO_Init(GPIOA, &GPIO_InitStructure);

 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;//MISO
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	SPI_software_W_SS(1);
	SPI_software_W_SCK(0);
	
}

/***
spi	起始条件：ss从高电平切为低电平

		终止条件：ss从低电平切为高电平

***/
void SPI_software_Start(void)
{
	SPI_software_W_SS(0);
}


void SPI_software_Stop(void)
{
	SPI_software_W_SS(1);
}

//掩码方式
uint8_t SPI_software_SwapByte_MaskOffCode(uint8_t ByteSend)
{
	
	uint8_t ByteReceive = 0x00;

	for(uint8_t i = 0; i <8; i++)
	{
		
		/***
			前两步是主机将数据移出操作 从机怎么操作我们不关心
		***/
		SPI_software_W_MOSI(ByteSend & (0x80 >> i));//主机拿出数据

		SPI_software_W_SCK(1);//时钟上升沿
		
	
		/***
			下面的操作是主机读取从机数据的操作
		***/
		if(SPI_software_R_MISO() == 1)//主机读取数据
		{
			/***
				ByteReceive相当于 00000000 每一次位移都在对每一位进行改变
				比如从机数据为1100 1011
				第一次获取到的就是1 
				第二次要右移 读到的也是1 
				第三次读到的是0 就不将ByteReceive或1了
			***/
			ByteReceive |= (0x80 >> i); //
			
			
		}
		
		SPI_software_W_SCK(0);//时钟下降沿
		
	}
	
	return ByteReceive;
}

//移位方式 效率高 但是会更改原始数据
uint8_t SPI_software_SwapByte_GressionCode(uint8_t ByteSend)
{

	for(uint8_t i = 0; i <8; i++)
	{
		SPI_software_W_MOSI(ByteSend & 0x80);//主机拿出数据
		
		ByteSend <<= 1;//将整个字节向左移动一位，最后一位自动补0
		
		SPI_software_W_SCK(1);//时钟上升沿
		
		if(SPI_software_R_MISO() == 1)//主机读取数据
		{
			
			/*
				放在发送数据的最低位 因为发送数据前一步已经 左移过，
				所以每次最后一位都是无效位，可以用来保存主机读取到的从机数据
			*/
			ByteSend |= 0x01; //
			SPI_software_W_SCK(0);//时钟下降沿
			
		}
		
		
		
	}
	
	return ByteSend;
}






