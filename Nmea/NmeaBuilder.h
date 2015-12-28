/********************************************************************
* NmeaBuilder.h
* Description:  This file contains the functions necessary to parse
*               incoming strings of data to for NMEA sentences and
*               check the checksum.
* Author:       K. Pattison
* Date:         24JAN2015
* *******************************************************************/
#ifndef _NMEABUILDER_H_
#define _NMEABUILDER_H_

/* Includes *********************************************************/


/* Defines **********************************************************/
typedef struct {
	char *talkerId;	
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

#endif
