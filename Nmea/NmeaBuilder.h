/********************************************************************
* NmeaBuilder.h
* Description:  This file contains the functions necessary to parse
*               incoming strings of data to for NMEA sentences and
*               check the checksum.
* Author:       K. Pattison
* Date:         24JAN2015
* *******************************************************************/
/* Includes *********************************************************/


/* Defines **********************************************************/
typedef struct {
	NmeaTalker_e talkerId;	
	char *payload;
	int	payloadLen;
	bool checksumValid;
} NmeaSenence_s

typedef enum {
	GPRMC,
	GPGGA,
	GPGSV,
	GPGST,
	GPGSA,
} NmeaTalker_e

/* Function Prototypes **********************************************/
NmeaSentence_s NmeaBuilder(char *inBuff, int inLen);

