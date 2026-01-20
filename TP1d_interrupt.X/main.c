#include "configbits.h" 
#include <xc.h>         
#define _XTAL_FREQ 8000000

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

/* Configuration du timer2 avec une période de 100 us */
void config_timer2(void){
PR2 = 24; 
T2CONbits.T2CKPS = 1; // Prescaler = 1:4
T2CONbits.T2OUTPS = 1; // Postscaler = 1:2
T2CONbits.TMR2ON = 1; // Timer2 activé
}
/* Configuration de l'interruption du Timer2 */
void config_interrupts(void){
    PIE1bits.TMR2IE = 1;    // Activer interrupt Timer 2
    PIR1bits.TMR2IF = 0;    //Mise a zéro du flag 
    INTCONbits.PEIE = 1;    
    INTCONbits.GIE = 1;    
}
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
   
    LATD = 0x00;// Mise à zéro des LED1-4
    LATB = 0x00;// Mise à zéro des LED5-8
    TRISD = 0x00; // Tout le port D en sortie 
    TRISB = 0x00; // Tout le port B en sortie 
    
    config_timer2(); //Appel de fonction
    config_interrupts();//Appel de fonction

    while(1){ 
        
    }
}
