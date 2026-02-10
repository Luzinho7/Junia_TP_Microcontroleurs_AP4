#include "configbits.h" // Bits de configuration
#include <xc.h>         // Definition des registres specifiques au uC
#include "lcd.h"
#include "spi.h"
#define _XTAL_FREQ 8000000

const char ALPHABET [] = "0123456789abcdefghijklmnopqrstuvwxyz";
const int ALPHABET_SIZE = 36;

int offset = 0;
int encryptionStatus = 0;

void uart_config(){
    
    PIE1bits.TXIE = 0;                      /* disable UART interrupts */
    PIE1bits.RCIE = 1;
    RC1STA = 0;                             /* turn off UART RX */
    TX1STA = 0;                             /* turn off UART TX */   
    RXPPS  = 0b10111;                       /* Assign RC7 to UART RX */
    RC6PPS = 0b10100;                       /* Assign UART TX to RC6 */
    
    TRISCbits.TRISC6 = 0;                             /* sets UART TX pin RC6 as an output */
    LATCbits.LATC6 = 0;
    TRISCbits.TRISC7 = 1; // RC7 : Entrée numérique
    ANSELCbits.ANSC7 = 0;
    
    SP1BRGL=12;// Registre SP1BRGL
    SP1BRGH=0; // Registres SP1BRGH
    
    TX1STAbits.SYNC = 0;  // Bit SYNC 
    TX1STAbits.BRGH = 0; // Bit BRGH 
    BAUD1CONbits.BRG16 = 0;// Bit BRG16 
    
    RC1STAbits.CREN = 1; // Activation des pins
    TX1STAbits.TXEN = 1;// Activation du TX
    RC1STAbits.SPEN = 1;// Activation du RX
}

char read (){
    return RC1REG;
}

void UART_SendChar(char data)
{
    while(PIR1bits.TXIF == 0);
    TX1REG = data;
}



void config_interrupts(void){
    INTCONbits.PEIE = 1;    
    INTCONbits.GIE = 1;     
}

void init_rb0(void){
    // Bouton RB0
    TRISBbits.TRISB0 = 1;
    ANSELBbits.ANSB0 = 0; 
    RD0PPS = 0x0F;
}


void config_adc(void){
        TRISAbits.TRISA0 = 1; 
        ANSELAbits.ANSA0 = 1; //Conversion Analogique
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

int get_val(char c) {
    // Gestion de '0'-'9
    if (c >= '0' && c <= '9') {
        return c - '0'; 
    }
    
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 10;
    }
    return -1; 
}

char cesar(char c) {
    int new_val;
    int val_cesar = get_val(c);
    if (c >= 'A' && c <= 'Z') {
        c = c + ('a' - 'A'); 
    }
    if (val_cesar == -1) return 0;
    
    if (encryptionStatus == 0) {
        new_val = (val_cesar + offset) % ALPHABET_SIZE;
    } else { 
        new_val = val_cesar - offset;
        while (new_val < 0) {
            new_val += ALPHABET_SIZE;
        }
        new_val = new_val % ALPHABET_SIZE;
    }
    return ALPHABET[new_val];
}

void __interrupt() isr(void) {
    
    char carac = read();
    char result = cesar(carac);
        // On renvoie une valeur valide
        if (result != 0) {
        UART_SendChar(result);
}
}
    
void affichage(void){
    LCD_Clear();
    LCD_GoTo(0,0);
    LCD_WriteString("Offset : ");
    LCD_WriteByte((offset / 10) + '0'); // Fonction dans LCD.h
    LCD_WriteByte((offset % 10) + '0'); // Fonction dans LCD.h
    
    LCD_GoTo(1,0);
    if (encryptionStatus){
        LCD_WriteString("Dechiffrement");
    } else {
        LCD_WriteString("Chiffrement");
    }
}

void init_offset(void){
    unsigned int val_adc = read_adc();
    // 255 (max Potentiomètre) / 7 = 36.4
    unsigned int new_offset = val_adc / 7;// On limite à 35
    
    if (new_offset >= ALPHABET_SIZE) {
        new_offset = ALPHABET_SIZE - 1;
    }
    //Maj de l'affichage
    if (new_offset != offset){
        offset = new_offset;
        affichage();
    }
}

void main(void) {
    
    //Initialisation du Boutton, potentiomètre et LCD.
    init_rb0();
    uart_config();    
    config_adc();
    SPI_InitializePins();
    LCD_InitializePins();
    SPI_Initialize();
    LCD_Initialize();
    
    
    read_adc(); // Première lecture du potentiomètre
    init_offset(); // Init offset
    affichage();     // Premier affichage
    config_interrupts();// Interruptions
    
    while(1){
        
        if (!PORTBbits.RB0) {
            __delay_ms(50); 
            if (!PORTBbits.RB0) {
                
                if (encryptionStatus == 0){ //En Chiffrement
                    encryptionStatus = 1; //En dechiffrement
                } else {
                    encryptionStatus = 0;//En Chiffrement
                }
                affichage(); // Affiche l'écran en temps réel
                
                while(!PORTBbits.RB0); 
                __delay_ms(50);
            }
        } 
        // Mise à jour de l'offset 
       init_offset();
        __delay_ms(10);
    }
}

