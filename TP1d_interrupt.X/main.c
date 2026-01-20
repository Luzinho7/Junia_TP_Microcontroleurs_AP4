#include "configbits.h"
#include <xc.h>
#include "leds.h"
#include "timers2.h"
#include "interrupts.h"

// Définitions des masques de LED
#define MASK_LED1 0X01 //LED1
#define MASK_LED2 0X02 //LED2
#define MASK_LED3 0X04 //LED3
#define MASK_LED4 0X08 //LED4
#define MASK_LED5 0X01 //LED5
#define MASK_LED6 0X02 //LED6
#define MASK_LED7 0X04 //LED7
#define MASK_LED8 0X08 //LED8

//Déclaration de variables pour l'interruption

unsigned int compteur_temps = 0; 
unsigned int LED = 0;

/*Routine d'interruption*/
void __interrupt() isr_toggle_LED (void){
    if (PIE1bits.TMR2IE && PIR1bits.TMR2IF){
        PIR1bits.TMR2IF = 0;
        compteur_temps++;
        
    if(compteur_temps >= 1250){
            compteur_temps = 0; // Remise à zéro du compteur
            
        LATB = 0x00;// Mise à zéro des LED5-8 
        LATD = 0x00;// Mise à zéro des LED1-4 
        //Etape pour allumage de la bonne 
        switch(LED){
                case 0: LATD |= MASK_LED1; break;
                case 1: LATD |= MASK_LED2; break;
                case 2: LATD |= MASK_LED3; break;
                case 3: LATD |= MASK_LED4; break;
                case 4: LATB |= MASK_LED5; break;
                case 5: LATB |= MASK_LED6; break;
                case 6: LATB |= MASK_LED7; break;
                case 7: LATB |= MASK_LED8; break;
            }
            // nouvelle étape 
            LED++;
            if(LED > 7) {
                LED = 0;
            }
        }
    }
}

void main(void) {
    
    led_init();
    config_timer2(); //Appel de fonction
    config_interrupts();//Appel de fonction

    while(1){ 
        
    }
}
