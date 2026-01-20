#include "interrupts.h"
#include <xc.h>

void config_interrupts(void){
    PIE1bits.TMR2IE = 1;    // Activer interrupt Timer 2
    PIR1bits.TMR2IF = 0;    // Mise a zéro du flag 
    INTCONbits.PEIE = 1;    
    INTCONbits.GIE = 1;     
}

