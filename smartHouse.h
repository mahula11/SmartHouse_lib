
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

//* structure of CanID
//* 0 - 15, 16 bitov je adresa zariadenia
//* 16 - 23, 8bitov pre typ spravy
//*          0 - správa bez špecifikovaného typu
//*          1 - žiadosť o poslanie celej conf
//*          2 - odpoveď na ziadost o poslanie celej conf - posiela celu conf
//*          3 - posiela pridanú conf
//*          4 - odoberá konkrétnu conf zo zariadenia
//*          5 - vypínač posiela správu(ziarovkam)
#define CANID_START_MAC_ADDRESS 0
#define CANID_END_MAC_ADDRESS 15
#define CANID_LENGTH_OF_MAC_ADDRESS 16
#define CANID_START_TYPE_IN_ID 16
#define CANID_END_TYPE_IN_ID 23
#define CANID_LENGTH_OF_TYPE 8

#define CANID_TYPE_NO_SPECIFICATION 0
#define CANID_TYPE_GET_WHOLE_CONF 1
#define CANID_TYPE_SEND_WHOLE_CONF 2
#define CANID_TYPE_ADD_CONF 3
#define CANID_TYPE_DEL_CONF 4
#define CANID_TYPE_SWITCH_SEND 5

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
	static bool isMessageFromCanConf(INT32U & id) {
		//* nastavime masku 16711680 = 0000 0000 ‭1111 1111 0000 0000 0000 0000‬
		int mask = 16711680;
		//* posunieme o 16 miest do prava, cize posunieme bity do prveho byte 
		uint8_t res = (id & mask) >> 16;
		return (res == CANID_TYPE_GET_WHOLE_CONF);
	}

	static INT32U getNormalizedID(INT32U id) {
		//* vycisti IDcko od bitov, ktore su konfiguracne, ktore nie su pre identifikator
		//* 65535 = 0000 0000 0000 0000 1111 1111 1111 1111
		int mask = 65535;
		id &= mask;
		return id;
	}
};

#endif