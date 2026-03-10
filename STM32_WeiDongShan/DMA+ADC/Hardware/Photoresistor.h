#ifndef __PHOTORESISTOR_H
#define __PHOTORESISTOR_H

#include <stdint.h>


#define ADC_LIST_LENGTH 3

typedef struct
{

	uint16_t ADC_list[ADC_LIST_LENGTH];
	

}ADC_paramater_t;
extern ADC_paramater_t ADC_paramater;



void AD_GetValue(void);
void AD_Init(void);
float adc_calculate(uint16_t adc_value);
#endif