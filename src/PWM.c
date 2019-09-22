/*
 * PWM.c
 *
 *  Created on: Sep 21, 2019
 *      Author: Hanna Muratovic
 */

#include <msp430fr4133.h>
#include "PWM.h"

void configure_PWM(void) {

    P1DIR |= BIT7; //P1.7 Output
    P1SEL0 |= BIT7; //P1.7 Select
}

void PWM_ON(void) {
    TA0CCR0 = 20000;           //Set the period in the Timer A0 Capture/Compare 0 register to 20 ms
    TA0CCR1 = 2000;              //controls duty cycle (us)
    TA0CTL = TASSEL_2 | MC_1;    //TASSEL selects SMCLK as clock source and MC_1 tells it to count up to the value in TA0CCR0
    TA0CCTL1 = OUTMOD_7;
}

void PWM_OFF(void) {
    TA0CCR1 = 0;              //controls duty cycle (us)
}


