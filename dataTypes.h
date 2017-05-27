#pragma once

#include <arduino.h>

//#include "smartHouse.h"


//* type of messages (size is 1byte)
const byte MSGTYPE_NO_SPECIFICATION = 0;
const byte MSGTYPE_FOR_CANCONF = 1;		//* CanDevice ask for whole configuration from CanConf
const byte MSGTYPE_FROM_CANCONF = 2;		//* CanConf send configuration to CanDevice
const byte MSGTYPE_FROM_CANCONF_ADD = 3;		//* CanConf add configuration to CanDevice
const byte MSGTYPE_FROM_CANCONF_DEL = 4;		//* CanConf send request for deleting configuration to CanDevice
const byte MSGTYPE_SWITCH_SEND = 5;		//* switch send msg to lights
const byte MSGTYPE_RESET = 6;		//* reset to all CanDevices

//* device types (size is 1byte)
const byte DEVICE_TYPE_SWITCH = 1;
const byte DEVICE_TYPE_PUSH_BUTTON = 2;
const byte DEVICE_TYPE_STAIR_CASE_SWITCH = 3;
const byte DEVICE_TYPE_LIGHT = 4;
const byte DEVICE_TYPE_LIGHT_WITH_DIMMER = 5;
const byte DEVICE_TYPE_SOCKET = 6;
const byte DEVICE_TYPE_THERMOMETER = 7;
const byte DEVICE_TYPE_FLOATATION_SENSOR = 8;
const byte DEVICE_TYPE_WINDOW_SWITCH = 9;
const byte DEVICE_TYPE_DOOR_SWITCH = 10;
const byte DEVICE_TYPE_HUMIDITY_SENSOR = 11;
const byte DEVICE_TYPE_PIR = 12;
const byte DEVICE_TYPE_LOCK = 13;
const byte DEVICE_TYPE_IBUTTON = 14;

typedef uint16_t MacID;		//* MediaAccessControl address - Netword address of device
typedef byte MsgData[8];

class CDataBase {
public:
	byte _type;

	CDataBase(byte type);

	virtual byte getSize();
	virtual void serialize(byte * pData) = 0;
	virtual void deserialize(byte * pData) = 0;

	byte getType();
	static byte getType(byte * pData);
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

