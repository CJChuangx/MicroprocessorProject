#include <xc.h>
#include <pic18f4520.h>
    //setting TX/RX

char mystring[20];
int lenStr = 0;

void UART_Initialize() {
           
/*       TODObasic   
           Serial Setting      
        1.   Setting Baud rate
        2.   choose sync/async mode 
        3.   enable Serial port (configures RX/DT and TX/CK pins as serial port pins)
        3.5  enable Tx, Rx Interrupt(optional)
        4.   Enable Tx & RX
 */
    TRISC = 0;
    TRISCbits.TRISC6 = 1;            
    TRISCbits.TRISC7 = 1;            
    
    //  Setting baud rate
    TXSTAbits.SYNC = 0;           
    BAUDCONbits.BRG16 = 0;          
    TXSTAbits.BRGH = 0;
    SPBRG = 51;      
    
   //   Serial enable
    RCSTAbits.SPEN = 1;              
    PIR1bits.TXIF = 0;//  flag bit
    PIR1bits.RCIF = 0;//  flag bit
    TXSTAbits.TXEN = 1;           
    RCSTAbits.CREN = 1;
    PIE1bits.TXIE = 0; // enable interrpt for transmisstion
    IPR1bits.TXIP = 0; // priority of transmit interrupt             
    PIE1bits.RCIE = 1; // enable interrupt for receive
    IPR1bits.RCIP = 1 ; // priority of reveive interrupt
          
    }

void UART_Write(unsigned char data)  // Output on Terminal
{
    while(!TXSTAbits.TRMT);
    TXREG = data;              //write to TXREG will send data 
    return;
}


void UART_Write_Text(char* text) { // Output on Terminal, limit:10 chars
    for(int i=0;text[i]!='\0';i++)
        UART_Write(text[i]);
}

void ClearBuffer(){
    for(int i = 0; i < 10 ; i++)
        mystring[i] = '\0';
    lenStr = 0;
}

char MyuartRead()
{
    /* TODObasic: try to use UART_Write to finish this function */
    char c = RCREG;
    if(c == '\r'){
        UART_Write('\n');
        UART_Write('\r');
    }
    else UART_Write(c);
    
    return c;
}

char *GetString(){
    return mystring;
}
