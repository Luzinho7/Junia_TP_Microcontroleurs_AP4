#include "../Ressources/configbits.h"
#include <xc.h>
#include <stdbool.h>

#define LED1 LATDbits.LATD0
#define DIR_LED1 TRISDbits.TRISD0


void config_pwm4(void){
PWM4DCH = 0; // Rapport cyclique (poids fort) : 0
PWM4DCL = 0; // Rapport cyclique (poids faible) : 0
// Soit rapport cyclique = [(25 << 2) + 0] / 4(249+1) = 0.1
PWM4CONbits.PWM4EN = 1; // Activer PWM4

RD0PPS = 0x0F; 
}


void led(void){
    DIR_LED1 = 0;
    LED1 = 1;  
    TRISB = 0; //LED 5 A 8 en sortie
}

void config_timer2(void){
PR2 = 249; // Période de Timer2 
T2CONbits.T2CKPS = 1; // Prescaler = 1:4
T2CONbits.T2OUTPS = 7; // Postscaler = 1:8
T2CONbits.TMR2ON = 1; // Activer Timer2

//0 à 250 montée + 250 descente = 500
//On veut 2s soit 2000ms
//2000ms / 500 = 4ms  1/8MHZ= 125 ns

}

void config_interrupts(void){
    PIE1bits.TMR2IE = 1;    // Activer interrupt Timer 2
    PIR1bits.TMR2IF = 0;    // Mise a zéro du flag 
    INTCONbits.PEIE = 1;    
    INTCONbits.GIE = 1;     
}

 int lum = 0;
 bool reverse = false;

void __interrupt() isr(void) {
    if (PIR1bits.TMR2IF) {
        PIR1bits.TMR2IF = 0;

        if(reverse) {
            lum--;
        } else {
            lum++;
        }
        
        PWM4DCH = lum;
        
        if (lum >= 249){
            reverse = true;
            lum = 249; 
        } else if (lum <= 0){
            reverse = false;
            lum= 0; 
        }
    }
}

void main(void) {
    led();
    config_timer2();
    config_interrupts();
    config_pwm4();
    
    while (1) {
       
    }
}


