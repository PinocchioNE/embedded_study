#ifndef __PHOTORESISTOR_H
#define __PHOTORESISTOR_H

#include <stdint.h>
uint16_t AD_GetValue(uint8_t ADC_Channel);
void AD_Init(void);
float adc_calculate(uint16_t adc_value);
#endif