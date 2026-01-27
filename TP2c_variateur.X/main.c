/*
 * File:   main.c
 * Author: Pierre et Lucas
 *
 * Created on 20 janvier 2026, 15:35
 */
#include <xc.h>
#include "../Ressources/configbits.h"

#define LED1 LATDbits.LATD0
#define DIR_LED1 TRISDbits.TRISD0
#define POT PORTAbits.RA0
#define DIR_POT TRISAbits.TRISA0



void config_adc(void){
TRISAbits.TRISA0 = 1; 
ANSELAbits.ANSA0 = 1; //Conversion Analogique
TRISD = 0; //LED 1 a 4 en sortie
TRISB = 0; //LED 5 A 8 en sortie
ADCON0bits.CHS = 0b00000; // Entrée : potentiomètre
ADCON1bits.ADFM = 0; // Format : justifié à gauche
ADCON0bits.ADON = 1; // ADC : en marche
}
/* Lecture de la valeur sur 8 bits */
char read_adc(void){
ADCON0bits.GO = 1; // Lancer la lecture de l?ADC
while(ADCON0bits.GO){} // Attendre la fin de l?acquisition
return ADRESH; // Retourner les 8bits de poids fort du résultat
}

void config_timer2(void){
T2CONbits.T2CKPS = 3; // Prescaler = 1:64
T2CONbits.T2OUTPS = 4; // Postscaler = 1:5
PR2 = 255; // Période de Timer2 
T2CONbits.TMR2ON = 1; // Activer Timer2
}
/* Configurer la PWM4 avec un rapport cyclique de 10% */
void config_pwm4(void){
PWM4DCH = 0; // Rapport cyclique (poids fort) : 0
PWM4DCL = 0; // Rapport cyclique (poids faible) : 0
// Soit rapport cyclique = [(25 << 2) + 0] / 4(249+1) = 0.1
PWM4CONbits.PWM4EN = 1; // Activer PWM4
DIR_LED1 = 0; // RB0 = sortie
RD0PPS = 0x0F; 
}


void led(void){
    DIR_LED1 = 0;
    LED1 = 1;
    DIR_POT = 1;
    ANSELAbits.ANSA0;   
}
void main(void) {
    char lum;
    config_timer2();// Appel de la fonction
    config_pwm4();// Appel de la fonction
    config_adc();
    led();
    
    while(1){ // boucle
        lum = read_adc() ;
        PWM4DCH = lum;
}
}

      