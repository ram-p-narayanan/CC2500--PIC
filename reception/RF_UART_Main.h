/* 
 * File:   RF_UARt_Main.h
 * Author: ram
 *
 * Created on September 30, 2014, 4:41 PM
 */

#ifndef RF_UART_MAIN_H
#define	RF_UART_MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif

// CONFIG

#define BIT_ON  1
#define BIT_OFF 0

static unsigned char ReceivedData;

void UARTInit(unsigned int BaudRate);
void UARTWriteLine(const char *str);
void UARTWriteString(const char *str);
void UARTWriteChar(char ch);
void UARTGotoNewLine();





#ifdef	__cplusplus
}
#endif

#endif	/* RF_UART_MAIN_H */

