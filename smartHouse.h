
#ifndef Morse_h
#define Morse_h

#include "Arduino.h"

#ifndef INT32U
#define INT32U unsigned long
#endif

#ifndef INT8U
#define INT8U byte
#endif


struct MASK_FILTER {
	INT32U maskRXM0;
	INT32U filterRXF0;
	INT32U filterFXR1;
	INT32U maskRXM1;
	INT32U filterRXF2;
	INT32U filterRXF3;
	INT32U filterRXF4;
	INT32U filterRXF5;
};


enum DEVICE_TYPE { switchButton, pushButton, stairCaseSwitch, light, lightWithDimmer, socket };
enum MESSAGE_TYPE { configRequest, configResponse, eventFromSwitch, eventFromPushButton };
//enum GPIO {1, 2};
enum ROUTABLE_MESSAGES { routable, noRoutable };

struct CONF_DEVICE {
	INT32U macID;		//* Identifikator z CanBus zariadenia (z EEPROM)
	//MASK_FILTER masksAndFilters;
	byte canSpeed;
	INT32U segment;
	DEVICE_TYPE deviceType;
};

struct CONF_MESSAGE {
	INT32U macID;	//* Identifikator z CanBus zariadenia (z EEPROM)
	byte confData[9];
	//DEVICE_TYPE deviceType;	//* urcenie zariadenia vzhladom na GPIO pin
	//INT8U gpio;		//* pin, ktory je pouzity (pri ziarovke/zasuvke ako vystupny, pri vypinaci ako vstupny, podla deviceType)
	//INT32U canID;			//* ID spravy, ktore bude poslane pri udalosti. ked to bude vypinac, tak bude poslana sprava s tymto ID a ziarovky/zasuvky to budu odchytavat
	//ROUTABLE_MESSAGES routable;	//* urci, ci sprava bude moct byt presmerovana do inych segmentov siete
};


class SmartHouse {
public:
	SmartHouse();
	~SmartHouse();
};

#endif