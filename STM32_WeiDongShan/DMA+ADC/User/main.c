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

uint8_t aaa = 0;
int main(void)
{
aaa = sizeof(ADC_paramater.ADC_list);
	/*OLED初始化*/
	OLED_Init();

	AD_Init();
	My_DMA_init();
	
	
	OLED_ShowString(1, 1, "AD_VALUE:", OLED_6X8);
	OLED_ShowString(1, 9, "Voltage: .  V", OLED_6X8);
	
	OLED_ShowString(1, 17, "AD_VALUE:", OLED_6X8);
	OLED_ShowString(1, 26, "Voltage: .  V", OLED_6X8);	
	
	OLED_ShowString(1, 35, "AD_VALUE:", OLED_6X8);
	OLED_ShowString(1, 44, "Voltage: .  V", OLED_6X8);
	
	while(1)
	{
		//光敏电阻
		AD_GetValue();
		ad_value_photo_resistor = ADC_paramater.ADC_list[0];
		Voltage_photo_resistor = adc_calculate(ad_value_photo_resistor);
		
		//霍尔
		ad_value_hall = ADC_paramater.ADC_list[2];
		Voltage_hall = adc_calculate(ad_value_hall);
				
		//热敏电阻
		ad_value_hot_resistor =  ADC_paramater.ADC_list[1];
		Voltage_hot_resistor = adc_calculate(ad_value_hot_resistor);

		
		
		OLED_ShowNum(54,1,ad_value_photo_resistor, 4,OLED_6X8);
			
		OLED_ShowNum(48,9,Voltage_photo_resistor, 1,OLED_6X8);
			
		OLED_ShowNum(60,9,(uint16_t)(Voltage_photo_resistor * 100) % 100, 2,OLED_6X8);
		
		
		
		OLED_ShowNum(54,17,ad_value_hall, 4,OLED_6X8);
			
		OLED_ShowNum(48,26,Voltage_hall, 1,OLED_6X8);
			
		OLED_ShowNum(60,26,(uint16_t)(Voltage_hall * 100) % 100, 2,OLED_6X8);
		
		
		
		OLED_ShowNum(54,35,ad_value_hot_resistor, 4,OLED_6X8);
			
		OLED_ShowNum(48,44,Voltage_hot_resistor, 1,OLED_6X8);
			
		OLED_ShowNum(60,44,(uint16_t)(Voltage_hot_resistor * 100) % 100, 2,OLED_6X8);
		
				
		
		
		
		Delay_ms(100);
		
		OLED_Update();
	
	}
	
}

