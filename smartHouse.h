
#ifndef Morse_h
#define Morse_h

#include <Arduino.h>

#include "dataTypes.h"
#include "CanID.h"

#define DEBUG_BUILD
#ifdef DEBUG_BUILD
#  define DEBUG(x) do {Serial << x << endl;} while (0)
#  define VAR(x) #x << F(":") << x
#  define PRINT_DATA(x) x[0] << "," << x[1] << "," <<  x[2] << "," << x[3] << "," << x[4] << "," << x[5] << "," << x[6] << "," << x[7]
#else
#  define DEBUG(x) do {} while (0)
#  define VAR(x) 
#  define PRINT_DATA(x) 
#endif

//struct MASK_FILTER {
//	uint32_t maskRXM0;
//	uint32_t filterRXF0;
//	uint32_t filterFXR1;
//	uint32_t maskRXM1;
//	uint32_t filterRXF2;
//	uint32_t filterRXF3;
//	uint32_t filterRXF4;
//	uint32_t filterRXF5;
//};

//* structure of CanID
//* 0 - 15, 16 bitov je adresa zariadenia
//* 16 - 23, 8bitov pre typ spravy
//*          0 - správa bez špecifikovaného typu
//*          1 - žiadosť o poslanie celej conf
//*          2 - odpoveď na ziadost o poslanie celej conf - posiela celu conf
//*          3 - posiela pridanú conf
//*          4 - odoberá konkrétnu conf zo zariadenia
//*          5 - vypínač posiela správu(ziarovkam)
//* 24 - 29, 6bitov - not used

//* CanID:
//* |    Not used    |     Type of message     |              MAC address              |
//* | 28 27 26 25 24 | 23 22 21 20 19 18 17 16 | 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0 |


struct CONF {
	//MacID macAddress;
	//uint8_t watchdogTimeout;
	//uint8_t autoResetTime;
	//byte count;
	CDataBase ** ppConfData;
};

class SmartHouse {
public:
	static CONF * newConf(byte count);
	//static CONF * newConf(byte count, MacID macAddress);
};

#endif
