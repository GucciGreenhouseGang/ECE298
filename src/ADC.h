/*
 * ADC.h
 *
 *  Created on: Sep 20, 2019
 *      Author: Hanna Muratovic
 */

#ifndef SRC_ADC_H_
#define SRC_ADC_H_


//variables
unsigned int ADCresult[3];                                    // 16-bit ADC conversion result array
unsigned char numADC;

//functions
void configure_ADC(void);
__interrupt void ADC_ISR(void);

#endif /* SRC_ADC_H_ */
