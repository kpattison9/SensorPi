/********************************************************************
* NmeaBuilder.c
* Description:  This file contains the functions necessary to parse
*               incoming strings of data to for NMEA sentences and
*               check the checksum.
* Author:       K. Pattison
* Date:         24JAN2015
* *******************************************************************/
/*Includes **********************************************************/
#include "NmeaBuilder.h"

/* Defines **********************************************************/
#DEFINE ASCII_CONV 48;

/* Typedefs *********************************************************/
typedef enum {
	SEARCH,
	TALKER,
	FILL,
	CHECKSUM
} NmeaState_e

/* Function Prototypes **********************************************/
NmeaTalker_e GetNmeaTalker(char *inBuff);
bool ValidateNmeaChecksum(char *inBuff, int inLen, char checksumA, char checksumB)

static NmeaState_e nmeaBuilderSm = SEARCH;
static char nmeaBuffer[256];
static int  strLen = 0;
static char checksumA;
static char checksumB;
static int  talkerCtr = 0;
static char talkerStr[5];
static char validTalkers[5][5] = {"GPRMC", "GPGGA", "GPGSV", "GPGST", "GPGSA"};
static NmeaTalker_e refTalkers[5] = {GPRMC, GPGGA, GPGSV, GPGST, GPGSA};

static NmeaTalker_e outputTalker;
static uint8_t outputLen;


/* NmeaBuilder outputs null if there is not a full sentence found, otherwise it outputs a validated NmeaSententce*/
NmeaSentence_s NmeaBuilder(char *inBuff, int inLen) {
	NmeaSentence_s retVal = NULL;
	
	for(int idx = 0; idx < inLen; idx++){
		switch (NmeaBuilderSm){
			case (SEARCH):
				if (inBuff[idx] == "$"){
					//nmeaBuffer[strLen++] = inBuf[idx];
					nmeaBuilderSm 			= TALKER;
				}
				break;
		   case(TALKER):
		   	/*Collect the entire string to validate the checksum*/
		   	nmeaBuffer[strLen++] = inBuf[idx];
		   	/*Collect the talker string*/
		   	if (talkerCtr < 5){
		   		talkerStr[talkerCnt++] = inBuff[idx];
		   	} else {
		   		/*Set the output TalkerID (since we wait for the else, we'll skip the following
		   		 * "," after the talker ID and can get straight to buffering the payload */
		   		outputTalker; = GetNmeaTalker(talkerStr);
		   		strLen = 0;
		   		NmeaBuilderSm  = FILL;
		   	}
		   	break;
			case(FILL):
				if (inBuff[idx] == "*"){
					nmeaBuilderSm 	= CHECKSUM_A;
				} else {
					nmeaBuffer[strLen++] = inBuff[idx];
				}
			   break;
			case(CHECKSUM_A):
				checksumA = inBuff[idx];
				nmeaBuilderSm = CHECKSUM_B;
		 		break;
		   case(CHECKSUM_B):
		   	checksumB = inBuff[idx];
		   	if (ValidateNmeaChecksum(*nmeaBuffer, strLen, checksumA, checksumB)){
		   		/*Allocate the output memory (strLen - 6 to accomodate the talker and first comma*/
		   		temp.payload = (char *) malloc ((strLen - 6) * sizeof(char));
		   		for(int idy = 0; idy < strLen; idy ++){
		   			temp.payload[idy] = nmeaBuffer[idy + 6];
		   		}

		   		temp.checksumValid = TRUE;
		   		temp.payloadLen = strLen;
		   		temp.talkerId = outputTalker;
		   	}
      }

	}

	return retVal;
}

/* GetNmeaTalker ************************************************************************
 * Description: This function compares the NmeaTalker string with a list of options to 
 *              output an enumerated version
 ****************************************************************************************/
NmeaTalker_e GetNmeaTalker(char *inBuff){
	NmeaTalker_e returnVal;
	for (int idx = 0, idx < 5, idx++){
		if(strcmp(inBuff, validTalkers[idx]) == 0){
			returnVal = refTalkers[idx];
			break;
		}
	}

	return returnVal;
}


/* ValidateNmeaChecksum ************************************************************************
 * Description: This function checks the Nmea Checksum
 ****************************************************************************************/
bool ValidateNmeaChecksum(char *inBuff, int inLen, char checksumA, char checksumB){
	/*Do the cheap ascii to int conversion */
	int rxChecksum = 10 * (checksumA - ASCII_CONV) + (checksumB - ASCII_CONV);
	int calcChecksum = 0;
	bool retVal;

	/*Calculate the Recieved Checksum*/
	for (int idx = 0; idx < inLen; idx++){
		calcChecksum ^= inBuff[idx];
	}

	if(rxChecksum == calcChecksum){
		retVal = TRUE;
	} else{
		retVal = FALSE;
	}
   
   return retVal;
}



	



