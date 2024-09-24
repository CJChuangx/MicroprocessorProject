#include "setting_hardaware/setting.h"
#include <stdlib.h>
#include <pic18f4520.h>
#include "stdio.h"
#include "string.h"
void main(void) {
    PORTD = 0;
    TRISD = 0;
    INTERRUPT_Initialize();
    UART_Initialize();
    OSCILLATOR_Initialize();
    while(1);
    return;
}
void __interrupt(high_priority)H_ISR(void){
    if(PIR1bits.RCIF == 1){
        char c = MyuartRead();
        c = c - '0';
        int i = 1;
        while(c>0) {i *=2;c--;}
        i--;
        PORTD = i * 16;
        PIR1bits.RCIF =0;
    }
    return;
}
