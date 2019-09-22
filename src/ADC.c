/*
 * ADC.c
 *
 *  Created on: Sep 20, 2019
 *      Author: Hanna Muratovic
 */

#include <msp430fr4133.h>
#include "ADC.h"

static uint8_t numADC = 2;
static uint16_t ADCresult[3];                                   // 16-bit ADC conversion result array

void configure_ADC(void) {
    // Configure ADC A3~5 pins
    SYSCFG2 |= ADCPCTL3 | ADCPCTL4 | ADCPCTL5;

    // Configure ADC
    ADCCTL0 |= ADCSHT_2 | ADCON;                                // 16ADCclks, ADC ON
    ADCCTL1 |= ADCSHP | ADCSHS_2 | ADCCONSEQ_3;                 // ADC clock MODCLK, sampling timer, TA1.1B trig.,repeat sequence
    //ADCCTL2 &= ~ADCRES;                                       // 8-bit conversion results
    ADCMCTL0 |= ADCINCH_5 | ADCSREF_1;                          // A0~2(EoS); Vref=1.5V
    ADCIE |= ADCIE0;                                            // Enable ADC conv complete interrupt

    // Configure reference
    PMMCTL0_H = PMMPW_H;                                        // Unlock the PMM registers
    PMMCTL2 |= INTREFEN;                                        // Enable internal reference
    __delay_cycles(400);                                        // Delay for reference settling
    __no_operation();

    // Configure TA1.1B as ADC trigger signal
    // Note: The TA1.1B is configured for 200us 50% PWM, which will trigger ADC
    // sample-and-conversion every 200us. The period of TA1.1B trigger event
    // should be more than the time period taken for ADC sample-and-conversion
    // and ADC interrupt service routine of each channel, which is about 57us in this code
    TA1CCR0 = 200-1;                                            // PWM Period, 200us
    TA1CCTL1 = OUTMOD_7;                                        // CCR1 reset/set
    TA1CCR1 = 100;                                              // CCR1 PWM duty cycle, 50%
    TA1CTL = TASSEL__SMCLK | MC__UP | TACLR;                    // SMCLK, up mode, clear TAR

    ADCCTL0 |= ADCENC;                                          // Enable ADC
    TA1CTL |= TACLR;                                            // Clear TAR to start the ADC sample-and-conversion
}

uint16_t retAmbient(void) {
    return ADCresult[0];
}

uint16_t retMoisture(char numZone) {
    return ADCresult[1];
}

uint16_t retTemperature(char numZone) {
    return ADCresult[2];
}

// ADC interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(ADC_VECTOR))) ADC_ISR (void)
#else
#error Compiler not supported!
#endif
{
    switch(__even_in_range(ADCIV,ADCIV_ADCIFG))
    {
        case ADCIV_NONE:
            break;
        case ADCIV_ADCOVIFG:
            break;
        case ADCIV_ADCTOVIFG:
            break;
        case ADCIV_ADCHIIFG:
            break;
        case ADCIV_ADCLOIFG:
            break;
        case ADCIV_ADCINIFG:
            break;
        case ADCIV_ADCIFG:
            ADCresult[numADC] = ADCMEM0;
            if(numADC == 0)
            {
                __no_operation();                               // Only for debugger
                numADC = 2;
            }
            else
            {
                numADC--;
            }
            break;
        default:
            break;
    }
}
