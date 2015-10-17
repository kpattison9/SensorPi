/********************************************************************
* Uart.c
* Description:  This file contains the functions necessary to 
                initialize, read and write the Pi's UART port.
* Author:       K. Pattison
* Date:         16OCT2015
* *******************************************************************/

#ifndef _UART_H_
#define _UART_H_


int InitUart();

unsigned int ReadUart(int devFilePtr, unsigned char *rxBuffer);






#endif