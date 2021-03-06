/********************************************************************
* Uart.c
* Description:  This file contains the functions necessary to 
                initialize, read and write the Pi's UART port.
* Author:       K. Pattison
* Date:         12AUG2015
* *******************************************************************/
/*Includes **********************************************************/
#include "uart.h"
#include <stdio.h>
#include <unistd.h>			//Used for UART
#include <fcntl.h>			//Used for UART
#include <termios.h>		   //Used for UART

/* Defines **********************************************************/
#define MAX_RD_LEN 256

/* Typedefs *********************************************************/

/* Function Prototypes **********************************************/

int InitUart(){
   //-------------------------
	//----- SETUP USART 0 -----
	//-------------------------
	//At bootup, pins 8 and 10 are already set to UART0_TXD, UART0_RXD (ie the alt0 function) respectively
	int uart0_filestream = -1;
	
	//OPEN THE UART
	//The flags (defined in fcntl.h):
	//	Access modes (use 1 of these):
	//		O_RDONLY - Open for reading only.
	//		O_RDWR - Open for reading and writing.
	//		O_WRONLY - Open for writing only.
	//
	//	O_NDELAY / O_NONBLOCK (same function) - Enables nonblocking mode. When set read requests on the file can return immediately with a failure status
	//											if there is no input immediately available (instead of blocking). Likewise, write requests can also return
	//											immediately with a failure status if the output can't be written immediately.
	//
	//	O_NOCTTY - When set and path identifies a terminal device, open() shall not cause the terminal device to become the controlling terminal for the process.

   
   uart0_filestream = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY );//| O_NDELAY);		//Open in non blocking read/write mode
	
	if (uart0_filestream == -1){
		//ERROR - CAN'T OPEN SERIAL PORT
		printf("Error - Unable to open UART.  Ensure it is not in use by another application\n");
	} else {
      //CONFIGURE THE UART
      //The flags (defined in /usr/include/termios.h - see http://pubs.opengroup.org/onlinepubs/007908799/xsh/termios.h.html):
      //	Baud rate:- B1200, B2400, B4800, B9600, B19200, B38400, B57600, B115200, B230400, B460800, B500000, B576000, B921600, B1000000, B1152000, B1500000, B2000000, B2500000, B3000000, B3500000, B4000000
      //	CSIZE:- CS5, CS6, CS7, CS8
      //	CLOCAL - Ignore modem status lines
      //	CREAD - Enable receiver
      //	IGNPAR = Ignore characters with parity errors
      //	ICRNL - Map CR to NL on input (Use for ASCII comms where you want to auto correct end of line characters - don't use for bianry comms!)
      //	PARENB - Parity enable
      //	PARODD - Odd parity (else even)
      struct termios options;
      tcgetattr(uart0_filestream, &options);
      options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;		//<Set baud rate
      options.c_iflag = IGNPAR;
      options.c_oflag = 0;
      options.c_lflag = 0;
      tcflush(uart0_filestream, TCIFLUSH);
      tcsetattr(uart0_filestream, TCSANOW, &options);
   }
	
   /*Return the device file handle */
	return uart0_filestream;

}

unsigned int ReadUart(int devFilePtr, unsigned char *rxBuffer){
	// Read up to 255 characters from the port if they are there
	//unsigned char rx_buffer[MAX_RD_LEN];
	int tempRxLen = read(devFilePtr, (void*)rxBuffer, MAX_RD_LEN -1);		//Filestream, buffer to store in, number of bytes to read (max)
	if (tempRxLen < 0)
	{
	   printf("Read Error \n");
	   //An error occured (will occur if there are no bytes)
	}
	else if (tempRxLen == 0)
	{
	   printf("No Data Waiting \n");
	   //No data waiting
	}
	else
	{

	   //Bytes received
	   rxBuffer[tempRxLen] = '\0';
	   //`rxLen = tempRxLen;
	   //printf("%i bytes read : %s\n", tempRxLen, rxBuffer);
	}
	
	return tempRxLen;

}

void CloseUart(int devFilePtr){
	close(devFilePtr);
}
