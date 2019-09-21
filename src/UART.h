/*
 * UART.h
 *
 *  Created on: Sep 20, 2019
 *      Author: Hanna Muratovic
 */

#ifndef SRC_UART_H_
#define SRC_UART_H_

void configure_UART(void);

__interrupt void USCI_A0_ISR(void);

#endif /* SRC_UART_H_ */
