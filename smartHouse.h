
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

#define MAC_ADDRESS_LENGTH 16	//* length of MAC address in bits


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
	CONF_MESSAGE(INT32U macID, unsigned char length, byte confData[]) {
		_macID = macID;
		_length = length;
		for (int i = 0; i < length; i++) {
			_confData[i] = confData[i];
		}
	};
	CONF_MESSAGE() {
		_macID = 0;
		_length = 0; 
	};

	INT32U _macID;	//* Identifikator z CanBus zariadenia (z EEPROM)
	byte _confData[9];
	unsigned char _length;
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

class CanExt {
public:
	static bool isMessageFromConfiguration(INT32U & id) {
		//* 27 bit v odpovedi znamena odpoved na ziadost o konfiguraciu
		return (bitRead(id, 27) == 1);
	}

	static INT32U getNormalizedID(INT32U id) {
		//* vycisti IDcko od bitov, ktore su konfiguracne, ktore nie su pre identifikator
		bitClear(id, 27);
		bitClear(id, 28);
		bitClear(id, 29);
		bitClear(id, 30);
		bitClear(id, 31);
		return id;
	}
};

#endif