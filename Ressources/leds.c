#include "leds.h"

void led_init(void){
    // Configuration des ports en sortie
    TRISD = 0x00; 
    TRISB = 0x00; 
    // LED éteinte
    LATD = 0x00;
    LATB = 0x00;
}

