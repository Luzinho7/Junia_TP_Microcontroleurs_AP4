#include "configbits.h" // Bits de configuration
#include <xc.h>         // Definition des registres specifiques au uC

#define _XTAL_FREQ 8000000

void uart_config(){
    
    PIE1bits.TXIE = 0;                      /* disable UART interrupts */
    PIE1bits.RCIE = 1;
    RC1STA = 0;                             /* turn off UART RX */
    TX1STA = 0;                             /* turn off UART TX */   
    RXPPS  = 0b10111;                       /* Assign RC7 to UART RX */
    RC6PPS = 0b10100;                       /* Assign UART TX to RC6 */
    
    TRISCbits.TRISC6 = 0;                             /* sets UART TX pin RC6 as an output */
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

void UART_SendString(const char *text)
{
    while(*text)
    {
        UART_SendChar(*text++);
    }
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

void main(void) {
    
    uart_config();             
    config_interrupts();
    
    while(1){
}
}