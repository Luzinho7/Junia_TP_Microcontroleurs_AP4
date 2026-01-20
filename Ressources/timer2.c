#include "timers2.h"

void config_timer2(void){
    PR2 = 24; 
    T2CONbits.T2CKPS = 1; // Prescaler = 1:4
    T2CONbits.T2OUTPS = 1; // Postscaler = 1:2
    T2CONbits.TMR2ON = 1; // Timer2 activé
}

