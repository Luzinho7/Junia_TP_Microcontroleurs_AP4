/*
 * File:   main.c
 * Author: apirog
 *
 * Created on January 5, 2026, 12:08 PM
 */

// Allume les LEDs D5-8 de la carte Microchip Explorer 8 
// MCU : PIC16F1719 
//
// | LED | Pin |
// |-----|-----|
// |  D5 | RB0 |
// |  D6 | RB1 |
// |  D7 | RB2 |
// |  D9 | RB3 |
//

#include <xc.h>
#include "../Ressources/configbits.h"

void main(void) {
    TRISB &= 0xF0;
    LATB  |= 0x0F;
    while(1);
}
