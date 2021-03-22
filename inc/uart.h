#ifndef UART_H_
#define UART_H_
int openUART();
float readFromUART(int uart0_filestream, unsigned char subcode);
float getInternalTemp();
float getPotentiometerTemp();
#endif 
