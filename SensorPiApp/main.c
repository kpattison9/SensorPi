#include "../Periph/uart.h"
#include "../Nmea/NmeaBuilder.h"
#include <unistd.h>			//Used for UART
#include <fcntl.h>			//Used for UART
#include <termios.h>		//Used for UART
void main(){
   int uartFp = InitUart();
   
   if (uartFp != -1) {
      unsigned char rxBuffer[256];
      int readLen;
      NmeaBuilder_s nmeaSentence;
      while(1){
      
         readLen = ReadUart(uartFp, rxBuffer);  
         
         nmeaSentence = NmeaBuilder(rxBuffer, readLen);
         if (nmeaSentence != NULL) {
            printf("Sentence: %s", nmeaSentence.payload);         
         }
         
         /* if(readLen > 0){
            printf("%d Bytes Read: %s\n", readLen, rxBuffer);
         } */
      }
   }
}
	
