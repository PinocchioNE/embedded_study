#include "stm32f10x.h"                  // Device header

#include "includes.h"
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
uint16_t ad_value_photo_resistor;
uint16_t ad_value_hot_resistor;
uint16_t ad_value_hall;
float Voltage_photo_resistor;
float Voltage_hot_resistor;
float Voltage_hall;
int main(void)
{

	/*OLED初始化*/
	OLED_Init();

	AD_Init();
	
	
	
	OLED_ShowString(1, 1, "AD_VALUE:", OLED_6X8);


	OLED_ShowString(1, 9, "Voltage: .  V", OLED_6X8);
	

	
	while(1)
	{
		//光敏电阻
		ad_value_photo_resistor = AD_GetValue(ADC_Channel_3);
		Voltage_photo_resistor = adc_calculate(ad_value_photo_resistor);
		
		//霍尔
		ad_value_hall = AD_GetValue(ADC_Channel_2);
		Voltage_hall = adc_calculate(ad_value_hall);
				
		//热敏电阻
		ad_value_hot_resistor =  AD_GetValue(ADC_Channel_1);
		Voltage_hot_resistor = adc_calculate(ad_value_hot_resistor);

		
		
		OLED_ShowNum(54,1,ad_value_photo_resistor, 4,OLED_6X8);
			
		OLED_ShowNum(48,9,Voltage_photo_resistor, 1,OLED_6X8);
			
		OLED_ShowNum(60,9,(uint16_t)(Voltage_photo_resistor * 100) % 100, 2,OLED_6X8);
		
		
		
		
		
		
		Delay_ms(100);
		
		OLED_Update();
	
	}
	
}
