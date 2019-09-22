/*
 * LCD.c
 *
 *  Created on: Sep 21, 2019
 *      Author: Hanna Muratovic
 */

#include <msp430fr4133.h>
#include "LCD.h"

#define pos1 4                                                 // Digit A1 - L4
#define pos2 6                                                 // Digit A2 - L6
#define pos3 8                                                 // Digit A3 - L8
#define pos4 10                                                // Digit A4 - L10
#define pos5 2                                                 // Digit A5 - L2
#define pos6 18                                                // Digit A6 - L18

// LCD memory map for numeric digits
const uint8_t digits[10] =
{
     0xFC,                                                      // "0"
     0x60,                                                      // "1"
     0xDB,                                                      // "2"
     0xF3,                                                      // "3"
     0x67,                                                      // "4"
     0xB7,                                                      // "5"
     0xBF,                                                      // "6"
     0xE4,                                                      // "7"
     0xFF,                                                      // "8"
     0xF7                                                       // "9"
};

// LCD memory map for uppercase letters
const uint8_t letters[26][2] =
{
    {0xEF, 0x00},  // "A"
    {0xF1, 0x50},  // "B"
    {0x9C, 0x00},  // "C"
    {0xF0, 0x50},  // "D"
    {0x9F, 0x00},  // "E"
    {0x8F, 0x00},  // "F"
    {0xBD, 0x00},  // "G"
    {0x6F, 0x00},  // "H"
    {0x90, 0x50},  // "I"
    {0x78, 0x00},  // "J"
    {0x0E, 0x22},  // "K"
    {0x1C, 0x00},  // "L"
    {0x6C, 0xA0},  // "M"
    {0x6C, 0x82},  // "N"
    {0xFC, 0x00},  // "O"
    {0xCF, 0x00},  // "P"
    {0xFC, 0x02},  // "Q"
    {0xCF, 0x02},  // "R"
    {0xB7, 0x00},  // "S"
    {0x80, 0x50},  // "T"
    {0x7C, 0x00},  // "U"
    {0x0C, 0x28},  // "V"
    {0x6C, 0x0A},  // "W"
    {0x00, 0xAA},  // "X"
    {0x00, 0xB0},  // "Y"
    {0x90, 0x28}   // "Z"
};

 void writeLCD(char c, uint8_t position)
 {
     if (c == ' ')
     {
         // Display space
         LCDMEM[position] = 0;
     }
     else if (c >= '0' && c <= '9')
     {
         // Display digit
         LCDMEM[position] = digits[c-48];
     }
     else if (c >= 'A' && c <= 'Z')
     {
         // Display alphabet
         LCDMEM[position] = letters[c-65][0] | (letters[c-65][1] << 8);
     }
 }

void configure_LCD(void) {
        // Configure XT1 oscillator
        P4SEL0 |= BIT1 | BIT2;                                              // P4.2~P4.1: crystal pins
        do
        {
            CSCTL7 &= ~(XT1OFFG | DCOFFG);                                  // Clear XT1 and DCO fault flag
            SFRIFG1 &= ~OFIFG;
        }while (SFRIFG1 & OFIFG);                                           // Test oscillator fault flag
        CSCTL6 = (CSCTL6 & ~(XT1DRIVE_3)) | XT1DRIVE_2;                     // Higher drive strength and current consumption for XT1 oscillator

        // Configure LCD pins
        SYSCFG2 |= LCDPCTL;                                        // R13/R23/R33/LCDCAP0/LCDCAP1 pins selected

        LCDPCTL0 = 0xFFFF;
        LCDPCTL1 = 0x07FF;
        LCDPCTL2 = 0x00F0;                                         // L0~L26 & L36~L39 pins selected

        LCDCTL0 = LCDSSEL_0 | LCDDIV_7;                            // flcd ref freq is xtclk

        // LCD Operation - Mode 3, internal 3.08v, charge pump 256Hz
        LCDVCTL = LCDCPEN | LCDREFEN | VLCD_6 | (LCDCPFSEL0 | LCDCPFSEL1 | LCDCPFSEL2 | LCDCPFSEL3);

        LCDMEMCTL |= LCDCLRM;                                      // Clear LCD memory

        LCDCSSEL0 = 0x000F;                                        // Configure COMs and SEGs
        LCDCSSEL1 = 0x0000;                                        // L0, L1, L2, L3: COM pins
        LCDCSSEL2 = 0x0000;

        LCDM0 = 0x21;                                              // L0 = COM0, L1 = COM1
        LCDM1 = 0x84;                                              // L2 = COM2, L3 = COM3

        LCDCTL0 |= LCD4MUX | LCDON;                                // Turn on LCD, 4-mux selected

        PMMCTL0_H = PMMPW_H;                                       // Open PMM Registers for write
        PMMCTL0_L |= PMMREGOFF_L;                                  // and set PMMREGOFF
}

void display_LCD(char zoneNumber, uint16_t zoneMoisture, uint16_t zoneTemp) {

    writeLCD('Z', pos1);
    writeLCD('O', pos2);
    writeLCD('N', pos3);
    writeLCD('E', pos4);
    writeLCD(' ', pos5);
    writeLCD(zoneNumber, pos6);

}
