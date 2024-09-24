#include <xc.h>
#include <pic18f4520.h>

void INTERRUPT_Initialize (void)
{
    RCONbits.IPEN = 1;      //enable Interrupt Priority mode
    INTCONbits.GIE = 1;
    INTCONbits.GIEH = 1;    //enable high priority interrupt
    INTCONbits.GIEL = 1;     //enable low priority interrupt
    return;
}
int button_enable(void){
    ADCON1 = 0x0f;
    TRISBbits.RB0 = 1;
    INTCONbits.INT0IE =1;
    INTCONbits.INT0IF = 0;
    return 0;
}
int timer2_enable(void){
// enable timer2 and its interrupt peroid = 0.5s
    PIR1bits.TMR2IF = 0;
    IPR1bits.TMR2IP = 0; // low priority
    PIE1bits.TMR2IE = 1; // enable TMR2 interrupt
    T2CON = 0xff; // enable timer2 and set frequency as 250KHz
    PR2 = 122;
    return 0;
}
void ADC_enable(void){
    PIE1bits.ADIE = 1;
    PIR1bits.ADIF = 0;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
    IPR1bits.ADIP = 0; // adc interrupt as low priority
    ADCON0bits.ADON = 1;
    ADCON0bits.GO = 1;
}

