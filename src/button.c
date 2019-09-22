/*
 * button.c
 *
 *  Created on: Sep 21, 2019
 *      Author: Hanna Muratovic
 */
#include <msp430fr4133.h>
#include "button.h"

static char zoneNumber;

void configure_button(void) {
    zoneNumber = '1';

    P1REN |= 0x04; // Resistor for P1.2
    P1OUT |= 0x04; // Resistor pulls up

    P1IES |= 0x04; // High to low transition for P1.2

    P1IFG &= ~BIT2; // P1.2 IFG cleared
    P1IE |= BIT2; // P1.2 interrupt enabled
}

char retNumZone(void) {
    return zoneNumber;
}

#pragma vector = PORT1_VECTOR
__interrupt void PORT1_ISR(void)
{
    // Increase zone number for zone selection
    if (zoneNumber >= '3') {
      zoneNumber = '1';
    } else {
        zoneNumber++;
    }
    P1IFG &= ~0x04; // Clear interrupt flag for P1.2
}
