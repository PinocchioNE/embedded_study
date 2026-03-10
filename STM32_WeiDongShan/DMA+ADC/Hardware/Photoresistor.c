#include "stm32f10x.h"
#include "Photoresistor.h"
ADC_paramater_t ADC_paramater;
void AD_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE);
		RCC_ADCCLKConfig(RCC_PCLK2_Div6);//ADC时钟分频  72M/6 = 12MHZ
	
	
    /* CS: PA3 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_2 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//模拟输入 不影响adc
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
		//注意采集转换的顺序就是按照 rank这个参数 这里就是PA3第一个采集
		ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2,ADC_SampleTime_55Cycles5);// 单通道 选择通道0 转换列表菜单中一共16个位置 这里选第一个 采样时间选55.5个cycle
		ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3,ADC_SampleTime_55Cycles5);	
		ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 1,ADC_SampleTime_55Cycles5);

		ADC_InitTypeDef ADC_InitStructure;
		ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//单次扫描
		ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//右对齐
		ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//软件触发 无触发源
		ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//独立模式 adc1和adc2各负责各自的
		ADC_InitStructure.ADC_NbrOfChannel = ADC_LIST_LENGTH;//可选范围1-16 即菜单列表长度 因为这里是非扫描 所以没有用 写一个就可以
		ADC_InitStructure.ADC_ScanConvMode = ENABLE;//扫描模式
		ADC_Init(ADC1, &ADC_InitStructure);
		
		ADC_Cmd(ADC1, ENABLE);//adc上电
		ADC_DMACmd(ADC1, ENABLE);//Enables or disables the specified ADC DMA request.
		ADC_ResetCalibration(ADC1);//复位校准
		while (ADC_GetResetCalibrationStatus(ADC1) == SET);//返回复位校准的状态 RESET就说明复位校准完成
		ADC_StartCalibration(ADC1);//开始校准
		while ( ADC_GetCalibrationStatus(ADC1) == SET);//校准完成
		
		
		
		
}

void AD_GetValue(void)
{

	DMA_Cmd(DMA1_Channel1, DISABLE);
	DMA_SetCurrDataCounter(DMA1_Channel1, ADC_LIST_LENGTH);
	DMA_Cmd(DMA1_Channel1, ENABLE);
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	
	while(DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);
	DMA_ClearFlag(DMA1_FLAG_TC1);
	
}


float adc_calculate(uint16_t adc_value)
{
	
	float adc_voltage;
	adc_voltage = (float)adc_value / 4095 * 3.3;
	
	
	
	return adc_voltage;
}