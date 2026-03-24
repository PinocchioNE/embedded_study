#include "stm32f10x.h"
#include "NM25Q128.h"
#include "SPI_hardware.h"



void NM25Q128_Init(void)
{
    SPI2_GPIO_Init();
    SPI_hardware_init();
		spi_data_init();
}


void spi_data_init(void)
{
	//给spi先发一个无效字节 清空DR 保证初始化
    SPI_hardware_W_SS(0);              // 片选拉低
    uint8_t val = NM25Q128_SPI2_read_write_byte(0xFF);  // 发一个 FF，读一字节
    SPI_hardware_W_SS(1);
   
}




uint8_t NM25Q128_SPI2_read_write_byte(uint8_t tx_data)
{
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET); //等发送缓冲空
    SPI_I2S_SendData(SPI2, tx_data);															  // 写入要发送的数据
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);// 等接收完成
    return (uint8_t)SPI_I2S_ReceiveData(SPI2);											// 返回本次收到的字节
}



void NM25Q128_ReadID(uint8_t *MID, uint16_t *DID, uint16_t order)
{

	
    SPI_hardware_W_SS(0);
	
		if(order == NM25Q128_CMD_READ_MANUFACTURER_ID)//0x90
		{
			NM25Q128_SPI2_read_write_byte(0x90); // 0x90
			NM25Q128_SPI2_read_write_byte(0x00);
			NM25Q128_SPI2_read_write_byte(0x00);
			NM25Q128_SPI2_read_write_byte(0x00);
			*DID = NM25Q128_SPI2_read_write_byte(0xFF) << 8;
			*DID |= NM25Q128_SPI2_read_write_byte(0xFF);
		}
		else if(order == NM25Q128_CMD_READ_JEDEC_ID)//0x9F
		{
			NM25Q128_SPI2_read_write_byte(0x9F);//给从机发信号 让从机回复设备信息
			*MID = NM25Q128_SPI2_read_write_byte(0xFF);//主机随便抛一个字节用户数据交换，获取设备信息
			*DID = NM25Q128_SPI2_read_write_byte(0xFF);//主机获取高8位数据
			*DID <<= 8;
			*DID |= NM25Q128_SPI2_read_write_byte(0xFF);//主机获取低八位数据
		
		}

    SPI_hardware_W_SS(1);
}





