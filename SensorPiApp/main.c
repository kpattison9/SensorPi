#include <uart.h>
#include <unistd.h>			//Used for UART
#include <fcntl.h>			//Used for UART
#include <termios.h>		//Used for UART
void main(){
   int uartFp = InitUart();
   
   if (uartFp != -1) {
      unsigned char rxBuffer[256];
      int readLen;
      while(1){
      
         readLen = ReadUart(uartFp, *rxBuffer);  

      }
   }
}
	
