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

uint8_t oled_x_length = 6;
uint8_t oled_y_length = 9;

int main(void)
{
	
	
	
	/*OLED初始化*/
	OLED_Init();
/******************ADC***********************************/
	#ifdef ADC_STUDY
		AD_Init();
		
		OLED_ShowString(1, 1, "AD_VALUE:", OLED_6X8);
		OLED_ShowString(1, 9, "Voltage: .  V", OLED_6X8);
		
		OLED_ShowString(1, 17, "AD_VALUE:", OLED_6X8);
		OLED_ShowString(1, 26, "Voltage: .  V", OLED_6X8);	
		
		OLED_ShowString(1, 35, "AD_VALUE:", OLED_6X8);
		OLED_ShowString(1, 44, "Voltage: .  V", OLED_6X8);	
	#endif

	
	
/******************DMA***********************************/
	#ifdef DMA_STUDY
	for(uint8_t i=0; i < 4; i++)
	{
			DMA_Parameter.DATA_A[i] = i;
			DMA_Parameter.DATA_B[i] = 0;
	}
	//转运前
	OLED_ShowHexNum(1, 1, DMA_Parameter.DATA_A[0], 1, OLED_6X8);
	OLED_ShowHexNum(1*oled_x_length, 1, DMA_Parameter.DATA_A[1], 1, OLED_6X8);
	OLED_ShowHexNum(2*oled_x_length, 1, DMA_Parameter.DATA_A[2], 1, OLED_6X8);
	OLED_ShowHexNum(3*oled_x_length, 1, DMA_Parameter.DATA_A[3], 1, OLED_6X8);
		
	OLED_ShowHexNum(1, 1*oled_y_length, DMA_Parameter.DATA_B[0], 1, OLED_6X8);
	OLED_ShowHexNum(1*oled_x_length, 1*oled_y_length, DMA_Parameter.DATA_B[1], 1, OLED_6X8);
	OLED_ShowHexNum(2*oled_x_length, 1*oled_y_length, DMA_Parameter.DATA_B[2], 1, OLED_6X8);
	OLED_ShowHexNum(3*oled_x_length, 1*oled_y_length, DMA_Parameter.DATA_B[3], 1, OLED_6X8);
			
	My_DMA_init((uint32_t)DMA_Parameter.DATA_A,(uint32_t)DMA_Parameter.DATA_B, 4);
	
	//转运后
	OLED_ShowHexNum(1, 2*oled_y_length, DMA_Parameter.DATA_A[0], 1, OLED_6X8);
	OLED_ShowHexNum(1*oled_x_length, 2*oled_y_length, DMA_Parameter.DATA_A[1], 1, OLED_6X8);
	OLED_ShowHexNum(2*oled_x_length, 2*oled_y_length, DMA_Parameter.DATA_A[2], 1, OLED_6X8);
	OLED_ShowHexNum(3*oled_x_length, 2*oled_y_length, DMA_Parameter.DATA_A[3], 1, OLED_6X8);
		
	OLED_ShowHexNum(1, 3*oled_y_length, DMA_Parameter.DATA_B[0], 1, OLED_6X8);
	OLED_ShowHexNum(1*oled_x_length, 3*oled_y_length, DMA_Parameter.DATA_B[1], 1, OLED_6X8);
	OLED_ShowHexNum(2*oled_x_length, 3*oled_y_length, DMA_Parameter.DATA_B[2], 1, OLED_6X8);
	OLED_ShowHexNum(3*oled_x_length, 3*oled_y_length, DMA_Parameter.DATA_B[3], 1, OLED_6X8);
			

		
	
	#endif
/*****************************************************/	
	while(1)
	{
	#ifdef ADC_STUDY
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
		
		
		
		OLED_ShowNum(54,17,ad_value_hall, 4,OLED_6X8);
			
		OLED_ShowNum(48,26,Voltage_hall, 1,OLED_6X8);
			
		OLED_ShowNum(60,26,(uint16_t)(Voltage_hall * 100) % 100, 2,OLED_6X8);
		
		
		
		OLED_ShowNum(54,35,ad_value_hot_resistor, 4,OLED_6X8);
			
		OLED_ShowNum(48,44,Voltage_hot_resistor, 1,OLED_6X8);
			
		OLED_ShowNum(60,44,(uint16_t)(Voltage_hot_resistor * 100) % 100, 2,OLED_6X8);
	#endif
				
				
	#ifdef DMA_STUDY
	
	
	#endif
		
		
		
		Delay_ms(100);
		
		OLED_Update();
	
	}
	
}
