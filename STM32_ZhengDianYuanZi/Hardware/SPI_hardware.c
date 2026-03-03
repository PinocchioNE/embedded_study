#include "stm32f10x.h"
#include "SPI_hardware.h"


void SPI_hardware_W_SS(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_12, (BitAction)BitValue);
}



void SPI2_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

    /* CS: PB12 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_SetBits(GPIOB, GPIO_Pin_12);

    /* SCK: PB13, MOSI: PB15 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* MISO: PB14 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//硬件配置下 miso要浮空 让硬件自己决定高低电平
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void SPI_hardware_init(void)
{

    SPI_InitTypeDef SPI_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

    SPI_I2S_DeInit(SPI2);
    SPI_StructInit(&SPI_InitStructure);

    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;//全双工
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;//mcu为主机
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;//每次8位
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;//模式0
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;//模式0
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;//cs片选位mcu控制 即自己控制片选引脚
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;//分频256
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;//高位先行
    SPI_InitStructure.SPI_CRCPolynomial = 7;//crc

    SPI_Init(SPI2, &SPI_InitStructure);

    SPI_Cmd(SPI2, ENABLE);

}
