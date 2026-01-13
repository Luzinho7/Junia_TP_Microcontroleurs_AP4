#include "configbits.h" 
#include <xc.h>         

#define _XTAL_FREQ 8000000

#define MASK_LED1 0X01
#define MASK_LED2 0X02
#define MASK_LED3 0X04
#define MASK_LED4 0X08
#define MASK_LED5 0X01
#define MASK_LED6 0X02
#define MASK_LED7 0X04
#define MASK_LED8 0X08

void config_timer2(void){
PR2 = 24; 
T2CONbits.T2CKPS = 1; 
T2CONbits.T2OUTPS = 1; 
T2CONbits.TMR2ON = 1; 
}

void wait_100us(void){
        while(!PIR1bits.TMR2IF){}
        PIR1bits.TMR2IF = 0;
    }

void wait_1s(void){
    unsigned int i; 
    for(i = 0; i < 10000; i++){
        wait_100us();
    }
}

void main(void) {
   
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
        wait_1s();
        LATD = 0x00;
        LATD |= MASK_LED2;
        wait_1s();
        LATD = 0x00;
        LATD |= MASK_LED3;
        wait_1s();
        LATD = 0x00;
        LATD |= MASK_LED4;
        wait_1s();
        LATD = 0x00;
        LATB |= MASK_LED5;
        wait_1s();
        LATB = 0x00;
        LATB |= MASK_LED6;
        wait_1s();
        LATB = 0x00;
        LATB |= MASK_LED7;
        wait_1s();
        LATB = 0x00;
        LATB |= MASK_LED8;
        wait_1s();
        LATB = 0x00
                ;
       
    }
}
