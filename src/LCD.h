/*
 * LCD.h
 *
 *  Created on: Sep 21, 2019
 *      Author: Hanna Muratovic
 */

#ifndef SRC_LCD_H_
#define SRC_LCD_H_

#include <stdint.h>

void configure_LCD(void);

void display_LCD(uint8_t zoneNumber, uint16_t zoneMoisture, uint16_t zoneTemp);

#endif /* SRC_LCD_H_ */
