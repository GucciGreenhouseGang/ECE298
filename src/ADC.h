/*
 * ADC.h
 *
 *  Created on: Sep 20, 2019
 *      Author: Hanna Muratovic
 */

#ifndef SRC_ADC_H_
#define SRC_ADC_H_

#include <stdint.h>

void configure_ADC(void);

uint16_t retAmbient(void);

uint16_t retMoisture(char numZone);

uint16_t retTemperature(char numZone);

__interrupt void ADC_ISR(void);

#endif /* SRC_ADC_H_ */
