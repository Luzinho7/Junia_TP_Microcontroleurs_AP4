#include "configbits.h" 
#include <xc.h>         

#define _XTAL_FREQ 8000000

// Définitions des masques de LED
#define MASK_LED1 0X01
#define MASK_LED2 0X02
#define MASK_LED3 0X04
#define MASK_LED4 0X08
#define MASK_LED5 0X01
#define MASK_LED6 0X02
#define MASK_LED7 0X04
#define MASK_LED8 0X08

/* Configuration du timer2 avec une période de 100 ms */
void config_timer2(void){
PR2 = 24; 
T2CONbits.T2CKPS = 1; // Prescaler = 1:4
T2CONbits.T2OUTPS = 1; // Postscaler = 1:2
T2CONbits.TMR2ON = 1; // Timer2 activé
}
/* Fonction d?attente bloquante utilisant le Timer2 */
void wait_100us(void){
        while(!PIR1bits.TMR2IF){}
        PIR1bits.TMR2IF = 0;
    }

void wait_125ms(void){
    unsigned int i; 
    for(i = 0; i < 1250 // 1250 boucles * 100us = 125 ms * 8 Led = 1000 ms soit 1 seconde car 1000/8 = 125 ms
            ; i++){
        wait_100us();
    }
}

void main(void) {
   
    LATD = 0x00;
    LATB = 0x00;
    
    config_timer2();
    
    TRISD &= MASK_LED1;
    TRISD &= MASK_LED2;
    TRISD &= MASK_LED3;
    TRISD &= MASK_LED4;
    TRISB &= MASK_LED5;
    TRISB &= MASK_LED6;
    TRISB &= MASK_LED7;
    TRISB &= MASK_LED8;
    
    

    while(1){ 
        
        LATD = 0x00;
        LATB = 0x00;
        
        LATD |= MASK_LED1;
        wait_125ms();
        LATD = 0x00;
        LATD |= MASK_LED2;
        wait_125ms();
        LATD = 0x00;
        LATD |= MASK_LED3;
        wait_125ms();
        LATD = 0x00;
        LATD |= MASK_LED4;
        wait_125ms();
        LATD = 0x00;
        LATB |= MASK_LED5;
        wait_125ms();
        LATB = 0x00;
        LATB |= MASK_LED6;
        wait_125ms();
        LATB = 0x00;
        LATB |= MASK_LED7;
        wait_125ms();
        LATB = 0x00;
        LATB |= MASK_LED8;
        wait_125ms();
        LATB = 0x00
                ;
       
    }
}
