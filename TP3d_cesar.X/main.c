#include "configbits.h" // Bits de configuration
#include <xc.h>         // Definition des registres specifiques au uC
#include "lcd.h"
#include "spi.h"
#define _XTAL_FREQ 8000000

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

void __interrupt() isr(void) {
    char carac = read();
    PIR1bits.RCIF = 0;  
    UART_SendChar (carac);
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


void main(void) {
    
    init_rb0();
    uart_config();    
    config_adc();
    read_adc();
    config_interrupts();
    SPI_InitializePins();
    LCD_InitializePins();
    SPI_Initialize();
    LCD_Initialize();
    
        
        int mode = 0;
        int bouton2 = 1;

        LCD_Clear();
        LCD_GoTo(0,0);
        LCD_WriteString("Offset : ");
        LCD_GoTo(1,0);
        LCD_WriteString("Chiffrement ");

    while(1){
        int bouton = PORTBbits.RB0;
        if (bouton == 0 && bouton2 == 1) {
            mode = !mode; 
            LCD_GoTo(1,0);
            if (mode == 1) {
                LCD_WriteString("Dechiffrement "); 
            } else {
                LCD_WriteString("Chiffrement   "); 
            }
            _delay(50);
}
}
}
