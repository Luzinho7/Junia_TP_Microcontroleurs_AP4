#include "configbits.h" // Bits de configuration
#include <xc.h>         // Definition des registres specifiques au uC

#define _XTAL_FREQ 8000000

#define MASK_LED1 0X01
#define MASK_LED2 0X02
#define MASK_LED3 0X04
#define MASK_LED4 0X08
#define MASK_LED5 0X01
#define MASK_LED6 0X02
#define MASK_LED7 0X04
#define MASK_LED8 0X08

void delai_approx(void){
    volatile long i;
    for(i=0 ; i< 100000; i++){}
                        }

void main(void) {
    /* Code d'initialisation */
    
    TRISD &= MASK_LED1;
    TRISD &= MASK_LED2;
    TRISD &= MASK_LED3;
    TRISD &= MASK_LED4;
    TRISB &= MASK_LED5;
    TRISB &= MASK_LED6;
    TRISB &= MASK_LED7;
    TRISB &= MASK_LED8;

    while(1){
        /* Code a executer dans une boucle infinie */
        
        LATD = 0x00;
        LATB = 0x00;
        
        LATD |= MASK_LED1;
        delai_approx();
        LATD = 0x00;
        LATD |= MASK_LED2;
        delai_approx();
        LATD = 0x00;
        LATD |= MASK_LED3;
        delai_approx();
        LATD = 0x00;
        LATD |= MASK_LED4;
        delai_approx();
        LATD = 0x00;
        LATB |= MASK_LED5;
        delai_approx();
        LATB = 0x00;
        LATB |= MASK_LED6;
        delai_approx();
        LATB = 0x00;
        LATB |= MASK_LED7;
        delai_approx();
        LATB = 0x00;
        LATB |= MASK_LED8;
        delai_approx();
        LATB = 0x00;
        
    }
}
