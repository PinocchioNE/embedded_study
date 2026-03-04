#include "stm32f10x.h"
#include "Photoresistor.h"

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
    
		//ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 1,ADC_SampleTime_55Cycles5);// 单通道 选择通道0 转换列表菜单中一共16个位置 这里选第一个 采样时间选55.5个cycle
	
	
	
		ADC_InitTypeDef ADC_InitStructure;
		ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//单次扫描
		ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//右对齐
		ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//软件触发 无触发源
		ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//独立模式 adc1和adc2各负责各自的
		ADC_InitStructure.ADC_NbrOfChannel = 1;//可选范围1-16 即菜单列表长度 因为这里是非扫描 所以没有用 写一个就可以
		ADC_InitStructure.ADC_ScanConvMode = DISABLE;//非扫描模式
		ADC_Init(ADC1, &ADC_InitStructure);
		
		ADC_Cmd(ADC1, ENABLE);//adc上电
		
		ADC_ResetCalibration(ADC1);//复位校准
		while (ADC_GetResetCalibrationStatus(ADC1) == SET);//返回复位校准的状态 RESET就说明复位校准完成
		ADC_StartCalibration(ADC1);//开始校准
		while ( ADC_GetCalibrationStatus(ADC1) == SET);//校准完成
		
}

uint16_t AD_GetValue(uint8_t ADC_Channel)
{
	ADC_RegularChannelConfig(ADC1, ADC_Channel, 1,ADC_SampleTime_55Cycles5);// 
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);//转换时间 72mhz/6分频 = 12mhz  采样总时间为 1 / 12mhz * 68（55.5个采样周期 + 12.5个固定转换周期） = 5.6微秒	
	return ADC_GetConversionValue(ADC1);

}


float adc_calculate(uint16_t adc_value)
{
	
	float adc_voltage;
	adc_voltage = (float)adc_value / 4095 * 3.3;
	
	
	
	return adc_voltage;
}