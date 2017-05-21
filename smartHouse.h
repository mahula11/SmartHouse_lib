
#ifndef Morse_h
#define Morse_h

#include <Arduino.h>

#define DEBUG_BUILD
#ifdef DEBUG_BUILD
#  define DEBUG(x) do {Serial << x;} while (0)
#else
#  define DEBUG(x) do {} while (0)
#endif

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
//* 24 - 29, 6bitov - not used
#define CANID_START_MAC_ADDRESS 0
#define CANID_END_MAC_ADDRESS 15
#define CANID_LENGTH_OF_MAC_ADDRESS 16
#define CANID_START_TYPE_IN_ID 16
#define CANID_END_TYPE_IN_ID 23
#define CANID_LENGTH_OF_TYPE 8

//* type of messages (size is 1byte)
#define MSGTYPE_NO_SPECIFICATION	0
#define MSGTYPE_FOR_CANCONF			1		//* CanDevice ask for whole configuration from CanConf
#define MSGTYPE_FROM_CANCONF		2		//* CanConf send configuration to CanDevice
#define MSGTYPE_FROM_CANCONF_ADD	3		//* CanConf add configuration to CanDevice
#define MSGTYPE_FROM_CANCONF_DEL	4		//* CanConf send request for deleting configuration to CanDevice
#define MSGTYPE_SWITCH_SEND			5		//* switch send msg to lights
#define MSGTYPE_RESET				6		//* reset to all CanDevices

//* device types (size is 1byte)
#define DEVICE_TYPE_SWITCH				1
#define DEVICE_TYPE_PUSH_BUTTON			2
#define DEVICE_TYPE_STAIR_CASE_SWITCH	3
#define DEVICE_TYPE_LIGHT				4
#define DEVICE_TYPE_LIGHT_WITH_DIMMER	5
#define DEVICE_TYPE_SOCKET				6
#define DEVICE_TYPE_THERMOMETER			7
#define DEVICE_TYPE_FLOATATION_SENSOR	8
#define	DEVICE_TYPE_WINDOW_SWITCH		9 
#define DEVICE_TYPE_DOOR_SWITCH			10
#define DEVICE_TYPE_HUMIDITY_SENSOR		11
#define DEVICE_TYPE_PIR					12
#define DEVICE_TYPE_LOCK				13
#define DEVICE_TYPE_IBUTTON				14

//* ------------DEVICES IN DETAIL------------ *//

//* device type LIGHT
//* in the configuration's data 
#define LIGHT_ADDR_IN_CONF_TYPE				0	//* type of device (1 byte)
#define LIGHT_ADDR_IN_CONF_GPIO				1	//* which GPIO connecting light (1 byte)
#define LIGHT_ADDR_IN_CONF_SWITCH_CANID		2	//* CanID of switch which will turn on/off light (2 bytes)
#define LIGHT_ADDR_IN_CONF_SWITCH_GPIO		4	//* GPIO of switch which will turn on/of light (1 byte)

//* device type SWITCH
//* in the message from switch
#define SWITCH_ADDR_IN_MSG__SWITCH_GPIO		0	//* GPIO of switch (1 byte)
#define SWITCH_ADDR_IN_MSG__SWITCH_VALUE	1	//* switch status (on/off - 0/255)
//* in the configuration's data
#define SWITCH_ADDR_IN_CONF_TYPE			0	//* type of device (1 byte)
#define SWITCH_ADDR_IN_CONF_GPIO			1	//* GPIO, which is connected to the switch (1 byte)



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

//* array for data from CanBus message
typedef byte MsgData[8];
//* array for configuration data
typedef byte ConfData[8];

//* CanID:
//* |                |     Type of message     |              MAC address              |
//* | 28 27 26 25 24 | 23 22 21 20 19 18 17 16 | 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0 |
typedef uint32_t CanID;		//* CanBus ID
typedef uint16_t MacID;		//* MediaAccessControl address - Netword address of device
typedef uint8_t  MsgType;	//* type of message

struct CONF_DATA {
	byte _length;
	ConfData _confData;

	CONF_DATA(byte length, ConfData * pConfData) {
		_length = length;
		for (int i = 0; i < length; i++) {
			_confData[i] = *pConfData[i];
		}
	}

	CONF_DATA() {
		_length = 0;
	}
};

//struct MSG_DATA {
//	MacID _macID;	//* Identifikator z CanBus zariadenia (z EEPROM)
//	byte _length;
//	MsgData _msgData;
//	//DEVICE_TYPE deviceType;	//* urcenie zariadenia vzhladom na GPIO pin
//	//INT8U gpio;		//* pin, ktory je pouzity (pri ziarovke/zasuvke ako vystupny, pri vypinaci ako vstupny, podla deviceType)
//	//INT32U canID;			//* ID spravy, ktore bude poslane pri udalosti. ked to bude vypinac, tak bude poslana sprava s tymto ID a ziarovky/zasuvky to budu odchytavat
//	//ROUTABLE_MESSAGES routable;	//* urci, ci sprava bude moct byt presmerovana do inych segmentov siete
//
//	MSG_DATA(MacID macID, byte length, MsgData * msgData) {
//		_macID = macID;
//		_length = length;
//		for (int i = 0; i < length; i++) {
//			_msgData[i] = *msgData[i];
//		}
//	}
//
//	MSG_DATA(MacID & macID, byte length, MsgData * msgData) {
//		_macID = macID;
//		_length = length;
//		for (int i = 0; i < length; i++) {
//			_msgData[i] = *msgData[i];
//		}
//	};
//
//	MSG_DATA() {
//		_macID = 0;
//		_length = 0;
//	};
//};

struct DATA_BASE {
	byte _type;
	byte _length;
	DATA_BASE(byte type, byte length) : _type(type), _length(length) {}
};

struct DATA_SWITCH : DATA_BASE {
	byte _gpio;
	DATA_SWITCH(byte gpio) : DATA_BASE(DEVICE_TYPE_SWITCH, 2), _gpio(gpio) {}
	byte * getBuf();
};

struct DATA_LIGHT : DATA_BASE {
	byte _gpio;
	MacID _switchCanID;
	byte _switchGPIO;
	DATA_LIGHT(byte gpio, MacID switchCanID, byte switchGPIO) : DATA_BASE(DEVICE_TYPE_LIGHT, 5), _gpio(gpio), _switchCanID(switchCanID), _switchGPIO(switchGPIO) {}
};

struct MSG_DATA {
	MacID _macID;	//* Identifikator z CanBus zariadenia (z EEPROM)
	DATA_BASE * _pData;
	//DEVICE_TYPE deviceType;	//* urcenie zariadenia vzhladom na GPIO pin
	//INT8U gpio;		//* pin, ktory je pouzity (pri ziarovke/zasuvke ako vystupny, pri vypinaci ako vstupny, podla deviceType)
	//INT32U canID;			//* ID spravy, ktore bude poslane pri udalosti. ked to bude vypinac, tak bude poslana sprava s tymto ID a ziarovky/zasuvky to budu odchytavat
	//ROUTABLE_MESSAGES routable;	//* urci, ci sprava bude moct byt presmerovana do inych segmentov siete
	
	MSG_DATA(MacID macID, DATA_BASE * pData) {
		_macID = macID;
		_pData = pData;
	}

	MSG_DATA() {
		_macID = 0;
		_pData = nullptr;
	};
};

struct CONF {
	MacID macAddress;
	byte count;
	CONF_DATA * pMsgs;
};

class SmartHouse {
public:
	SmartHouse();
	~SmartHouse();

	static CONF * newConf(byte count) {
		newConf(count, 0);
	}

	static CONF * newConf(byte count, MacID macAddress) {
		CONF * conf = new CONF;
		conf->count = count;
		conf->macAddress = macAddress;
		conf->pMsgs = new CONF_DATA[count];
		return conf;
	}
};

class CanExt {
private:
	static MsgType getConfigPartFromID(CanID & id) {
		//* nastavime masku 16711680 = 0000 0000 ‭1111 1111 0000 0000 0000 0000‬
		int mask = 16711680;
		//* posunieme o 16 miest do prava, cize posunieme bity do prveho byte 
		return (id & mask) >> 16;
	}

	static bool isMsgFlag(CanID & id, byte flag1) {
		MsgType res = getConfigPartFromID(id);
		if (res == flag1) { // || res == CANID_MSGTYPE_ADD_CONF || res == CANID_MSGTYPE_DEL_CONF) {
			return true;
		} else {
			return false;
		}
	}

	static bool isMsgFlag(CanID & id, byte flag1, byte flag2) {
		MsgType res = getConfigPartFromID(id);
		if (res == flag1 || res == flag2) { // || res == CANID_MSGTYPE_DEL_CONF) {
			return true;
		} else {
			return false;
		}
	}

	static bool isMsgFlag(CanID & id, byte flag1, byte flag2, byte flag3) {
		MsgType res = getConfigPartFromID(id);
		if (res == flag1 || res == flag2 || res == flag3) {
			return true;
		} else {
			return false;
		}
	}


public:
	static bool isMsgFlagFromSwitch(CanID & id) {
		return isMsgFlag(id, MSGTYPE_SWITCH_SEND);
	}

	static void setMsgFlagFromSwitch(CanID & id) {
		bitSet(id, 31);				//* set extended message
		//* v tomto pripade posunieme 16x 5tku do lava, dostaneme ju do casti, kde mame konfiguraciu
		//* 0101 --> 0101 0000 0000 0000 0000
		//* CanBus ID je hodnota od 0 do 16bitov
		//* cize ked tieto hodnoty spocitame (logicky OR), tak budeme mat konfiguraciu s IDckom
		id += (MSGTYPE_SWITCH_SEND << 16);
	}

	static bool isMsgFlagForConfiguration(CanID & id) {
		return isMsgFlag(id, MSGTYPE_FOR_CANCONF);
	}

	static void setMsgFlagForConfiguration(CanID & id) {		
		bitSet(id, 31);				//* set extended message
		bitSet(id, 30);				//* set remote flag
		id += (MSGTYPE_FOR_CANCONF << 16);
	}

	static bool isMsgFlagFromConfiguration(CanID & id) {
		return isMsgFlag(id, MSGTYPE_FROM_CANCONF, MSGTYPE_FROM_CANCONF_ADD, MSGTYPE_FROM_CANCONF_DEL);
	}

	static void setMsgFlagFromConfiguration(CanID & id) {
		bitSet(id, 31);				//* set extended message
		id += (MSGTYPE_FROM_CANCONF << 16);
	}

	static MacID getDeviceID(CanID id) {
		//* vycisti IDcko od bitov, ktore su konfiguracne, ktore nie su pre identifikator
		//* 65535 = 0000 0000 0000 0000 1111 1111 1111 1111
		int mask = 65535;
		id &= mask;
		return id;
	}

	static byte getDeviceTypeFromConf(ConfData * pConfData) {
		return *pConfData[0];
	}

	static byte getLightGPIO(ConfData * pConfData) {
		return *pConfData[LIGHT_ADDR_IN_CONF_GPIO];
	}

	static byte getSwitchGPIO_fromMsg(MsgData * pConfData) {
		return *pConfData[SWITCH_ADDR_IN_MSG__SWITCH_GPIO];
	}
	static byte getSwitchGPIO_fromConf(ConfData * pConfData) {
		return *pConfData[SWITCH_ADDR_IN_CONF_GPIO];
	}

	static byte getSwitchValue_fromMsg(MsgData * pConfData) {
		return *pConfData[SWITCH_ADDR_IN_MSG__SWITCH_VALUE];
	}
	
	static void setSwitchGPIO_toMsg(MsgData * pConfData, byte pin) {
		*pConfData[SWITCH_ADDR_IN_MSG__SWITCH_GPIO] = pin;
	}

	static void setSwitchValue_toMsg(MsgData * pConfData, byte value) {
		*pConfData[SWITCH_ADDR_IN_MSG__SWITCH_VALUE] = value;
	}

	static bool isDeviceLight(ConfData * pConfData) {
		//* Type is in first position in the DATA	
		return (DEVICE_TYPE_LIGHT == *pConfData[LIGHT_ADDR_IN_CONF_TYPE]);
	}

	static CanID getLightsSwitchCanID(ConfData * pConfData) {
		return *pConfData[LIGHT_ADDR_IN_CONF_SWITCH_CANID];
	}

	static byte getLightsSwitchGPIO(ConfData * pConfData) {
		return *pConfData[LIGHT_ADDR_IN_CONF_SWITCH_GPIO];
	}

	//* insert MacID to CanID
	static void setMacIdToCanID(CanID & canId, MacID macId) {
		canId += macId;
	}
};

#endif
