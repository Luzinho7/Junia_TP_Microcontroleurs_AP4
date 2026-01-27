/*
 * File:   main.c
 * Author: Pierre et Lucas
 *
 * Created on 20 janvier 2026, 15:35
 */
#include <xc.h>
#include "../Ressources/configbits.h"

void config_timer2(void){
T2CONbits.T2CKPS = 3; // Prescaler = 1:64
T2CONbits.T2OUTPS = 4; // Postscaler = 1:5
PR2 = 249; // Période de Timer2 pour 40ms
T2CONbits.TMR2ON = 1; // Activer Timer2
}
/* Configurer la PWM4 avec un rapport cyclique de 10% */
void config_pwm4(void){
PWM4DCH = 0; // Rapport cyclique (poids fort) : 0
PWM4DCL = 0; // Rapport cyclique (poids faible) : 0
// Soit rapport cyclique = [(25 << 2) + 0] / 4(249+1) = 0.1
PWM4CONbits.PWM4EN = 1; // Activer PWM4
}

void init_rb0(void){
    // Bouton RB0
    TRISBbits.TRISB0 = 1;
    ANSELBbits.ANSB0 = 0; 
    RD0PPS = 0x0F;
}

void led(void){
    TRISDbits.TRISD0 = 0; // LED D1
    
}
void main(void) {
    
    config_timer2();// Appel de la fonction
    config_pwm4();// Appel de la fonction
    init_rb0();// Appel de la fonction
    led();// Appel de la fonction
    
    while(1){ // boucle
        
        if (PORTBbits.RB0 == 0){ // Si bouton appuyé 
            PWM4DCH = 249; // Luminosité très forte
        }
        else{ // Sinon 
            PWM4DCH = 24; // Luminosité faible
        }
    }
    
}
