#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "W25Q64.h"
#include "SPI_hardware.h"
#include "NM25Q128.h"
/**
  * 坐标轴定义：
  * 左上角为(0, 0)点
  * 横向向右为X轴，取值范围：0~127
  * 纵向向下为Y轴，取值范围：0~63
  * 
  *       0             X轴           127 
  *      .------------------------------->
  *    0 |
  *      |
  *      |
  *      |
  *  Y轴 |
  *      |
  *      |
  *      |
  *   63 |
  *      v
  * 
  */

uint8_t aa =0x02;
int main(void)
{

	/*OLED初始化*/
	OLED_Init();

	OLED_ShowHexNum(1,1,aa, 2,OLED_6X8);
			
	OLED_ShowHexNum(1,8,(uint32_t)&aa, 8,OLED_6X8);
					


	
	OLED_Update();
	

	
	while(1)
	{
	
	}
	
}
