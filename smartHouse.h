﻿
#ifndef Morse_h
#define Morse_h

#include <Arduino.h>

struct MASK_FILTER {
	uint32_t maskRXM0;
	uint32_t filterRXF0;
	uint32_t filterFXR1;
	uint32_t maskRXM1;
	uint32_t filterRXF2;
	uint32_t filterRXF3;
	uint32_t filterRXF4;
	uint32_t filterRXF5;
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

//* type of messages
#define CANID_MSGTYPE_NO_SPECIFICATION	0
#define CANID_MSGTYPE_WHOLE_CONF		1
#define CANID_MSGTYPE_SEND_WHOLE_CONF	2
#define CANID_MSGTYPE_ADD_CONF			3
#define CANID_MSGTYPE_DEL_CONF			4
#define CANID_MSGTYPE_SWITCH_SEND		5
#define CANID_MSGTYPE_RESET				6

//* device types
#define DEVICE_TYPE_SWITCH				0
#define DEVICE_TYPE_PUSH_BUTTON			1
#define DEVICE_TYPE_STAIR_CASE_SWITCH	2
#define DEVICE_TYPE_LIGHT				3
#define DEVICE_TYPE_LIGHT_WITH_DIMMER	4
#define DEVICE_TYPE_SOCKET				5

//* device type LIGHT
#define STRUCT_LIGHT__TYPE			0	//* type
#define STRUCT_LIGHT__GPIO			1	//* GPIO, where is a light
#define STRUCT_LIGHT__SWITCH_CANID	2	//* canId of device, where is a switch (16bits)
#define STRUCT_LIGHT__SWITCH_GPIO	3	//* GPIO number, where is switch conected

//enum DEVICE_TYPE { switchButton, pushButton, stairCaseSwitch, light, lightWithDimmer, socket };
//enum MESSAGE_TYPE { configRequest, configResponse, eventFromSwitch, eventFromPushButton };
//enum GPIO {1, 2};
//enum ROUTABLE_MESSAGES { routable, noRoutable };

//struct CONF_DEVICE {
//	uint32_t macID;		//* Identifikator z CanBus zariadenia (z EEPROM)
//	//MASK_FILTER masksAndFilters;
//	byte canSpeed;
//	uint32_t segment;
//	DEVICE_TYPE deviceType;
//};

struct CONF_MESSAGE {
	uint16_t _macID;	//* Identifikator z CanBus zariadenia (z EEPROM)
	uint8_t _length;
	uint8_t _confData[8];
	//DEVICE_TYPE deviceType;	//* urcenie zariadenia vzhladom na GPIO pin
	//INT8U gpio;		//* pin, ktory je pouzity (pri ziarovke/zasuvke ako vystupny, pri vypinaci ako vstupny, podla deviceType)
	//INT32U canID;			//* ID spravy, ktore bude poslane pri udalosti. ked to bude vypinac, tak bude poslana sprava s tymto ID a ziarovky/zasuvky to budu odchytavat
	//ROUTABLE_MESSAGES routable;	//* urci, ci sprava bude moct byt presmerovana do inych segmentov siete
	
	CONF_MESSAGE(uint16_t & macID, unsigned char length, byte confData[]) {
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
};

struct CONF {
	uint16_t macAddress;
	byte count;
	CONF_MESSAGE * pMsgs;
};



class SmartHouse {
public:
	SmartHouse();
	~SmartHouse();

	static CONF * newConf(byte count) {
		newConf(count, 0);
	}

	static CONF * newConf(byte count, uint16_t macAddress) {
		CONF * conf = new CONF;
		conf->count = count;
		conf->macAddress = macAddress;
		conf->pMsgs = new CONF_MESSAGE[count];
		return conf;
	}
};

class CanExt {
private:
	static uint8_t getConfigPartFromID(uint32_t & id) {
		//* nastavime masku 16711680 = 0000 0000 ‭1111 1111 0000 0000 0000 0000‬
		int mask = 16711680;
		//* posunieme o 16 miest do prava, cize posunieme bity do prveho byte 
		return (id & mask) >> 16;
	}

public:
	static bool isMsgFlagConfiguration(uint32_t & id) {
		uint8_t res = getConfigPartFromID(id);
		if (res == CANID_MSGTYPE_WHOLE_CONF || res == CANID_MSGTYPE_ADD_CONF || res == CANID_MSGTYPE_DEL_CONF) {
			return true;
		} else {
			return false;
		}
	}

	static bool isMsgFlagFromSwitch(uint32_t & id) {
		uint8_t res = getConfigPartFromID(id);
		if (res == CANID_MSGTYPE_SWITCH_SEND) {
			return true;
		} else {
			return false;	
		}
	}

	static bool isMsgFlag(uint32_t & id, byte flag) {

	}

	static void setMsgFlagConfiguration(uint32_t & canID) {
		//* clear part of ID (which is for configuration)
		for (int i = 16; i < 24; i++) {
			bitClear(canID, i);
		}
		bitSet(canID, 31);				//* set extended message
		bitSet(canID, 30);				//* set remote flag
		bitSet(canID, 16);				//* set 1 to 3third word in ID - it's request for whole configuration
	}

	static uint16_t getDeviceID(uint32_t id) {
		//* vycisti IDcko od bitov, ktore su konfiguracne, ktore nie su pre identifikator
		//* 65535 = 0000 0000 0000 0000 1111 1111 1111 1111
		int mask = 65535;
		id &= mask;
		return id;
	}
};

#endif