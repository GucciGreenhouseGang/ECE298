/*
 * button.h
 *
 *  Created on: Sep 21, 2019
 *      Author: Hanna Muratovic
 */

#ifndef SRC_BUTTON_H_
#define SRC_BUTTON_H_

void configure_button(void);

char retNumZone(void);

__interrupt void PORT1_ISR(void);

#endif /* SRC_BUTTON_H_ */
