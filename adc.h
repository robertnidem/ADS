/*
 * adc.h
 *
 *  Created on: 27 jul 2022
 *      Author: rober
 */

#ifndef ADC_H_
#define ADC_H_


void ADC0_Init();
void ADC_Read(uint32_t* v, uint32_t* i, uint32_t* t);

#endif /* ADC_H_ */
