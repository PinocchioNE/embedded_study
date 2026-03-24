#include "stm32f10x.h"
#include "W25Q64.h"
#include "SPI_software.h"
#include "W25Q64_Instruction.h"



void W25Q64_Init(void)
{

	SPI_software_Init();

}


void W25Q64_ReadID(uint8_t *MID, uint16_t *DID)//MID厂商 DID设备ID
{
	SPI_software_Start();
	SPI_software_SwapByte_MaskOffCode(W25Q64_CMD_READ_JEDEC_ID);//给从机发信号 让从机回复设备信息
	*MID = SPI_software_SwapByte_MaskOffCode(W25Q64_DUMMY_BYTE);//主机随便抛一个字节用户数据交换，获取设备信息
	*DID = SPI_software_SwapByte_MaskOffCode(W25Q64_DUMMY_BYTE);//主机获取高8位数据
	*DID <<= 8;
	*DID |= SPI_software_SwapByte_MaskOffCode(W25Q64_DUMMY_BYTE);//主机获取低八位数据
	SPI_software_Stop();
}

//写使能
void W25Q64_WriteEnable(void)
{
	SPI_software_Start();
	SPI_software_SwapByte_MaskOffCode(W25Q64_CMD_WRITE_ENABLE);
	SPI_software_Stop();
}


//读状态寄存器 查看是否busy
void W25Q64_WaitBusy(void)
{
	uint32_t Timeout;
	SPI_software_Start();	
	SPI_software_SwapByte_MaskOffCode(W25Q64_CMD_READ_STATUS_REG1);
	Timeout = 10000;
	
	while((SPI_software_SwapByte_MaskOffCode(W25Q64_DUMMY_BYTE) & 0x01) == 0x01)
	{
		Timeout--;
		
		if(0 == Timeout)
		{
			break;
		
		}
	} 
	
	SPI_software_Stop();
}



//页编程
void W25Q64_PageProgram(uint32_t Address, uint8_t *DataArray, uint16_t Count)
{
	
	uint16_t i;
	
	W25Q64_WriteEnable();
	
	
	SPI_software_Start();
	SPI_software_SwapByte_MaskOffCode(W25Q64_CMD_PAGE_PROGRAM);
	//规定发送三次地址信息 即24位
	SPI_software_SwapByte_MaskOffCode(Address >> 16);
	SPI_software_SwapByte_MaskOffCode(Address >> 8);
	SPI_software_SwapByte_MaskOffCode(Address);
	for( i = 0; i < Count; i++)
	{
		SPI_software_SwapByte_MaskOffCode(DataArray[i]);
	
	} 
	SPI_software_Stop();
	
	W25Q64_WaitBusy();
}

//扇区擦除
void W25Q64_SectorErase(uint32_t Address)
{
	
	uint16_t i;
	
	W25Q64_WriteEnable();
	
	
	SPI_software_Start();
	SPI_software_SwapByte_MaskOffCode(W25Q64_CMD_SECTOR_ERASE_4K);
	//规定发送三次地址信息 即24位
	SPI_software_SwapByte_MaskOffCode(Address >> 16);
	SPI_software_SwapByte_MaskOffCode(Address >> 8);
	SPI_software_SwapByte_MaskOffCode(Address);
	SPI_software_Stop();
	
	W25Q64_WaitBusy();
}


//读数据
void W25Q64_ReadData(uint32_t Address, uint8_t *DataArray, uint32_t Count)
{
	uint32_t i;
	SPI_software_Start();
	SPI_software_SwapByte_MaskOffCode(W25Q64_CMD_READ_DATA);
	//规定发送三次地址信息 即24位
	SPI_software_SwapByte_MaskOffCode(Address >> 16);
	SPI_software_SwapByte_MaskOffCode(Address >> 8);
	SPI_software_SwapByte_MaskOffCode(Address);
	for( i = 0; i < Count; i++)
	{
		DataArray[i] = SPI_software_SwapByte_MaskOffCode(W25Q64_DUMMY_BYTE);
	
	}
	
	SPI_software_Stop();	
	
	
}