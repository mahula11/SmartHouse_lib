#pragma once

#include <arduino.h>

//#include "smartHouse.h"

//* messages types (size is 1byte, part of CanID (16-23bits))
const byte TYPE__NO_SPECIFICATION = 0;
const byte TYPE__ASK_FOR_CONF = 1;					//* CanDevice ask for whole configuration from CanConf
const byte TYPE__FROM_CONF__COUNT = 2;				//* count of configurations
const byte TYPE__FROM_CONF__SET_SIMPLE_SWITCH = 3;  //* configuration messages for devices
const byte TYPE__FROM_CONF__SET_SIMPLE_LIGHT = 4;
const byte TYPE__FROM_CONF__SET_WATCHDOG_TIMEOUT = 5;
const byte TYPE__FROM_SWITCH = 20;					//* switch send msg to lights
const byte TYPE__ASK_SWITCH_FOR_VALUE = 21;			//* after restart canDevice, light ask to switch for values

//* Aliases for DEVICE_TYPE
const byte DEVICE_TYPE_LIGHT = TYPE__FROM_CONF__SET_SIMPLE_LIGHT;
const byte DEVICE_TYPE_SWITCH = TYPE__FROM_CONF__SET_SIMPLE_SWITCH;
const byte DEVICE_TYPE_WATCHDOG_TIMEOUT = TYPE__FROM_CONF__SET_WATCHDOG_TIMEOUT;

const byte idsFromConf[] = {
		TYPE__FROM_CONF__COUNT,
		TYPE__FROM_CONF__SET_SIMPLE_LIGHT,
		TYPE__FROM_CONF__SET_SIMPLE_SWITCH,
		TYPE__FROM_CONF__SET_WATCHDOG_TIMEOUT,
		0
};

//* type of messages (size is 1byte)
const byte MSGTYPE_NO_SPECIFICATION = 0;
//const byte MSGTYPE_FOR_CANCONF = 1;			//* CanDevice ask for whole configuration from CanConf
//const byte MSGTYPE_FROM_CANCONF = 2;		//* CanConf send configuration to CanDevice
//const byte MSGTYPE_FROM_CANCONF_ADD = 3;	//* CanConf add configuration to CanDevice
//const byte MSGTYPE_FROM_CANCONF_DEL = 4;	//* CanConf send request for deleting configuration to CanDevice
//const byte MSGTYPE_SWITCH_SEND = 5;			//* switch send msg to lights
//const byte MSGTYPE_RESET = 6;				//* reset to CanDevices
//const byte MSGTYPE_ALARM = 7;				//* send alarm (lights flashing, unlock locks, sockets off, etc)
//const byte MSGTYPE_ASK_SWITCH_FOR_VALUE = 8;//* after restart canDevice, lights ask switch for values

//* device types (size is 1byte)
//const byte DEVICE_TYPE_SWITCH = 1; // msgtype_fromSimpleSwitch 
//const byte DEVICE_TYPE_PUSH_BUTTON = 2; //msgtype_
//const byte DEVICE_TYPE_STAIR_CASE_SWITCH = 3;
//const byte DEVICE_TYPE_LIGHT = 4;
//const byte DEVICE_TYPE_LIGHT_WITH_DIMMER = 5;
//const byte DEVICE_TYPE_SOCKET = 6;
//const byte DEVICE_TYPE_THERMOMETER = 7;
//const byte DEVICE_TYPE_FLOATATION_SENSOR = 8;
//const byte DEVICE_TYPE_WINDOW_SWITCH = 9;
//const byte DEVICE_TYPE_DOOR_SWITCH = 10;
//const byte DEVICE_TYPE_HUMIDITY_SENSOR = 11;
//const byte DEVICE_TYPE_PIR = 12;
//const byte DEVICE_TYPE_LOCK = 13;
//const byte DEVICE_TYPE_IBUTTON = 14;
//const byte DEVICE_TYPE_SMOKE_SENSOR = 15;
//const byte DEVICE_TYPE_BUZZER = 16;
//const byte DEVICE_TYPE_WATCHDOG_TIMEOUT = 17;

typedef uint16_t MacID;		//* MediaAccessControl address - Netword address of device
typedef byte MsgData[8];

enum WATCHDOG_TIMEOUT {
	to250ms, to500ms, to1000ms, to2000ms, to4000ms, to8000ms
};

class CDataBase {
public:
	byte _type;
	bool _modeForEeprom;

	CDataBase(byte type);
	void setModeForEeprom(bool mode);

	virtual byte getSize();
	virtual void serialize(byte * pData) = 0;
	virtual void deserialize(byte * pData) = 0;

	byte getType();
};

class CTrafficDataSwitch : public CDataBase {
public:
	byte _gpio;
	byte _value;

	CTrafficDataSwitch(byte gpio, byte value);
	CTrafficDataSwitch(byte * pDeserializeData);

	byte getSize();
	void serialize(byte * pData);
	void deserialize(byte * pData);
};

class CConfDataSwitch : public CDataBase {
public:
	byte _gpio;

	CConfDataSwitch();
	CConfDataSwitch(byte gpio);
	CConfDataSwitch(byte * pDeserializeData);

	byte getSize();
	void serialize(byte * pData);
	void deserialize(byte * pData);
};

class CConfDataLight : public CDataBase {
public:
	byte _gpio;
	MacID _switchMacID;
	byte _switchGPIO;

	CConfDataLight();
	CConfDataLight(byte * pDeserializeData);
	CConfDataLight(byte gpio, MacID switchCanID, byte switchGPIO);

	byte getSize();
	void serialize(byte * pData);
	void deserialize(byte * pData);
};

class CConfDataWatchdog : public CDataBase {
public :
	uint8_t _to; //* WATCHDOG_TIMEOUT

	CConfDataWatchdog();
	CConfDataWatchdog(byte * pDeserializeData);
	CConfDataWatchdog(uint8_t to);

	byte getSize();
	void serialize(byte * pData);
	void deserialize(byte * pData);
};

//class CConfDataReset : public CDataBase {
//public:
//	CConfDataReset();
//	CConfDataReset(byte * pDeserializeData);
//
//	byte getSize();
//	void serialize(byte * pData);
//	void deserialize(byte * pData);
//};
