#include<pic.h>
#include "RF_UART_Main.h"
// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.




void UARTInit(unsigned int BaudRate)
{
    switch (BaudRate)
    {
        case 9600:
            SPBRG = 103; // This value is set for a clock of 16 MHz
            break;
        case 19200:
            break;
        case 28800:
            break;
        case 33600:
            break;
        case 4800:
            break;
    }

    //TXSTA
    TXSTAbits.TX9    =  BIT_OFF;  //8 bit transmission
    TXSTAbits.TXEN   =  BIT_ON; //Transmit enable
    TXSTAbits.SYNC   =  BIT_OFF; //Async mode
    TXSTAbits.BRGH   =  BIT_ON; //High speed baud rate

    //RCSTA
    RCSTAbits.SPEN   =  BIT_ON;   //Serial port enabled
    RCSTAbits.RX9    =  BIT_OFF;    //8 bit mode
    RCSTAbits.CREN   =  BIT_ON;   //Enable receive
    RCSTAbits.ADDEN  =  BIT_OFF;  //Disable address detection

}

void UARTWriteLine(const char *str)
{
    UARTWriteChar('\r');//CR
    UARTWriteChar('\n');//LF

    UARTWriteString(str);
}

void UARTWriteString(const char *str)
{
  while(*str!='\0')
  {
      UARTWriteChar(*str);
      str++;
  }
}

void UARTWriteChar(char ch)
{
  while(!PIR1bits.TXIF);

  TXREG =   ch;
}

void UARTGotoNewLine()
{
    UARTWriteChar('\r');//CR
    UARTWriteChar('\n');//LF
}




