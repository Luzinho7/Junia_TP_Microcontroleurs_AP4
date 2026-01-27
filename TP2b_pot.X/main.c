/*
 * File:   main.c
 * Author: Pierre et Lucas
 *
 * Created on 27 janvier 2026, 
 */
#include <xc.h>
#include "../Ressources/configbits.h"

#define POT PORTAbits.RA0
#define DIR_POT TRISAbits.TRISA0

#define LED1 LATDbits.LATD0
#define LED2 LATDbits.LATD1
#define LED3 LATDbits.LATD2
#define LED4 LATDbits.LATD3
#define LED5 LATBbits.LATB0
#define LED6 LATBbits.LATB1
#define LED7 LATBbits.LATB2
#define LED8 LATBbits.LATB3


/* Configurer l?ADC pour lire la température interne */
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



void main(void) {
    
    config_adc();
    read_adc();
    
while(1) {
    if(read_adc() < 32){
        LED1 = 1;
        LED2=0;
    LED3=0;
    LED4=0;
    LED5=0;
    LED6=0;
    LED7=0;
    LED8=0;
        
    }else if (read_adc() < 64){
        LED2 = 1;
        LED1=0;
    LED3=0;
    LED4=0;
    LED5=0;
    LED6=0;
    LED7=0;
    LED8=0;
    }
    else if (read_adc() < 96){
        LED3 = 1;
    LED1=0;
    LED2=0;
    LED4=0;
    LED5=0;
    LED6=0;
    LED7=0;
    LED8=0;
}
    else if (read_adc() < 128){
        LED4 = 1;
    LED2=0;
    LED3=0;
    LED1=0;
    LED5=0;
    LED6=0;
    LED7=0;
    LED8=0;}
    else if (read_adc() < 160){
        LED5 = 1;
    LED2=0;
    LED3=0;
    LED4=0;
    LED1=0;
    LED6=0;
    LED7=0;
    LED8=0;}
    else if (read_adc() < 192){
        LED6 = 1;
    LED2=0;
    LED3=0;
    LED4=0;
    LED5=0;
    LED1=0;
    LED7=0;
    LED8=0;}
    else if (read_adc() <  224){ 
        LED7 = 1;
    LED2=0;
    LED3=0;
    LED4=0;
    LED5=0;
    LED6=0;
    LED1=0;
    LED8=0;}
    else {
        LED8 = 1;
    LED2=0;
    LED3=0;
    LED4=0;
    LED5=0;
    LED6=0;
    LED7=0;
    LED1=0;
    }
    
}
}