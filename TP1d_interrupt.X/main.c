#include "configbits.h"
#include <xc.h>

#define _XTAL_FREQ 8000000

// Masques des LEDs
#define MASK_LED1 0x01
#define MASK_LED2 0x02
#define MASK_LED3 0x04
#define MASK_LED4 0x08
#define MASK_LED5 0x01
#define MASK_LED6 0x02
#define MASK_LED7 0x04
#define MASK_LED8 0x08

// Variable globale pour suivre quelle LED est allumée (1 à 8)
// "volatile" est nécessaire car cette variable est modifiée dans l'interruption
volatile unsigned char led_actuelle = 1; 

// ---------------------------------------------------------------------------
// 1. Routine d'Interruption (ISR)
// Cette fonction est appelée AUTOMATIQUEMENT toutes les 100 us
// ---------------------------------------------------------------------------
void __interrupt() isr(void) {
    
    // On vérifie si c'est bien le Timer 2 qui appelle (au cas où il y en aurait d'autres)
    if(PIR1bits.TMR2IF == 1) {
        
        // IMPORTANT : On doit acquitter (baisser le drapeau) sinon l'interruption boucle à l'infini
        PIR1bits.TMR2IF = 0;

        // Variable statique : elle garde sa valeur entre deux appels de l'interruption
        static unsigned int compteur = 0; 
        
        compteur++; // On incrémente le compteur de ticks (1 tick = 100us)

        // Si on atteint 1250 ticks (1250 * 100us = 125 ms)
        if(compteur >= 1250) {
            compteur = 0; // Reset du compteur
            
            // --- Logique du Chenillard ---
            
            // 1. On éteint tout pour éviter les superpositions
            LATD = 0x00;
            LATB = 0x00;
            
            // 2. On allume la bonne LED selon la variable "led_actuelle"
            switch(led_actuelle) {
                case 1: LATD = MASK_LED1; break;
                case 2: LATD = MASK_LED2; break;
                case 3: LATD = MASK_LED3; break;
                case 4: LATD = MASK_LED4; break;
                case 5: LATB = MASK_LED5; break;
                case 6: LATB = MASK_LED6; break;
                case 7: LATB = MASK_LED7; break;
                case 8: LATB = MASK_LED8; break;
            }
            
            // 3. On prépare la prochaine LED pour le prochain passage (dans 125ms)
            led_actuelle++;
            if(led_actuelle > 8) {
                led_actuelle = 1; // Retour à la première LED
            }
        }
    }
}

// ---------------------------------------------------------------------------
// 2. Configuration du Timer 2 (100 us)
// ---------------------------------------------------------------------------
void config_timer2(void){
    PR2 = 24;              
    T2CONbits.T2CKPS = 1;  // Prescaler 1:4
    T2CONbits.T2OUTPS = 1; // Postscaler 1:2
    T2CONbits.TMR2ON = 1;  // Timer ON
}

// ---------------------------------------------------------------------------
// 3. Configuration des Interruptions
// ---------------------------------------------------------------------------
void config_interrupts(void){
    // Autoriser l'interruption spécifique du Timer 2
    PIE1bits.TMR2IE = 1; 
    
    // Autoriser les interruptions de périphériques (Timer 2 est un périphérique)
    INTCONbits.PEIE = 1;
    
    // Autoriser les interruptions Globales (Le disjoncteur général)
    INTCONbits.GIE = 1;
}

// ---------------------------------------------------------------------------
// 4. Main (Vide ou presque)
// ---------------------------------------------------------------------------
void main(void) {
    
    // Initialisation des Ports en Sortie
    TRISD = 0x00;
    TRISB = 0x00;
    
    // Initialisation état bas
    LATD = 0x00;
    LATB = 0x00;
    
    // Initialisation Timer et Interruptions
    config_timer2();
    config_interrupts(); // Ne pas oublier ça !

    // Allumer la première LED pour commencer proprement (optionnel)
    LATD = MASK_LED1;

    // Boucle infinie VIDE
    // Le processeur ne fait RIEN ici. Tout se passe dans "void __interrupt() isr()"
    while(1){
        // Vide
    }
}