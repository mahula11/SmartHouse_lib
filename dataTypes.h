#pragma once

#include <arduino.h>

#include "CanID.h"
#include "dataTypesDefinitions.h"


//#include "smartHouse.h"

//* messages types (size is 1byte, part of CanID (16-23bits))
const byte TYPE__NO_SPECIFICATION = 0;
const byte TYPE__ASK_FOR_CONF = 1;					//* CanDevice ask for whole configuration from CanConf
const byte TYPE__FROM_CONF__COUNT = 2;				//* count of configurations
const byte TYPE__FROM_CONF__SET_SIMPLE_SWITCH = 3;  //* simple classic switch, two positions, for turn on must press upside, to turn off must press downside
const byte TYPE__FROM_CONF__SET_SIMPLE_LIGHT = 4;   //* light turn on or off
const byte TYPE__FROM_CONF__SET_WATCHDOG_TIMEOUT = 5;
const byte TYPE__FROM_CONF__RESET = 6;				//* send reset to processor
const byte TYPE__FROM_CONF__SET_AUTO_RESET = 7;     //* set time for automatic reset
const byte TYPE__FROM_CONF__SET_CANBUS_SPEED = 8;   //* set speed for CAN BUS
const byte TYPE__FROM_CONF__SET_SWITCH_AS_BUTTON = 9; //* switch as classic button, for turn on must press upside, after release upside it goes back
const byte TYPE__FROM_CONF__SET_NEW_CONFIGURATION = 10; //* set new configuration
const byte TYPE__FROM_SWITCH = 20;					//* switch send msg to lights
const byte TYPE__ASK_SWITCH_FOR_VALUE = 21;			//* after restart canDevice, light ask to switch for values
const byte TYPE__FROM_ANY_DEVICE__PING = 22;		//* send ping to canBus
const byte TYPE__FROM_ANY_DEVICE__IM_UP = 23;		//* send message about start

//* Aliases for DEVICE_TYPE
const byte DEVICE_TYPE_LIGHT = TYPE__FROM_CONF__SET_SIMPLE_LIGHT;
const byte DEVICE_TYPE_SWITCH = TYPE__FROM_CONF__SET_SIMPLE_SWITCH;
const byte DEVICE_TYPE_WATCHDOG_TIMEOUT = TYPE__FROM_CONF__SET_WATCHDOG_TIMEOUT;
const byte DEVICE_TYPE_SWITCH_BUTTON = TYPE__FROM_CONF__SET_SWITCH_AS_BUTTON;

const byte idsFromConf[] = {
		TYPE__FROM_CONF__COUNT,
		TYPE__FROM_CONF__SET_SIMPLE_LIGHT,
		TYPE__FROM_CONF__SET_SIMPLE_SWITCH,
		TYPE__FROM_CONF__SET_WATCHDOG_TIMEOUT,
		TYPE__FROM_CONF__RESET,
		TYPE__FROM_CONF__SET_AUTO_RESET,
		TYPE__FROM_CONF__SET_CANBUS_SPEED,
		TYPE__FROM_CONF__SET_SWITCH_AS_BUTTON,
		TYPE__FROM_CONF__SET_NEW_CONFIGURATION,
		0
};

//* type of messages (size is 1byte)
//const byte MSGTYPE_NO_SPECIFICATION = 0;
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
typedef uint8_t MsgData[8];

#define CANBUS__COUNT_OF_SPEEDS 15
extern const char* canBusSpeeds[];

//* can be used when message should be received and processed with all devices on networks
#define CANBUS__MESSAGE_TO_ALL 0

enum WATCHDOG_TIMEOUT {
	to250ms, to500ms, to1000ms, to2000ms, to4000ms, to8000ms
};

enum AUTO_RESET_TIMES {
	arDisable, ar10s, ar1m, ar15m, ar1h, ar2h, ar3h, ar4h, ar5h, ar6h, ar7h, ar8h
};

class CDataBase {
public:
	static byte s_type;
	static byte getType();
	//* Conf messages send type against traffic messages where we don't send type
	bool _modeForEeprom;
	CanID _destCanID;

	CDataBase(byte type, MacID macId);
	//* when saving messagess to eeprom, must go there type of message, 
	//* otherwise, when sending messages through network, type of message is in CanID, no in data fields
	void setModeForEeprom(bool mode);

	virtual byte getSize();
	virtual void serialize(byte * pData) = 0;
	virtual void deserialize(byte * pData) = 0;
};

DEFINE_CLASS_MSG2_H(CTrafficMsg_fromSwitch, uint8_t, gpio, uint8_t, value)
DEFINE_CLASS_MSG1_H(CTrafficMsg_askSwitchForData, uint8_t, gpio)
DEFINE_CLASS_MSG1_H(CConfMsg_numOfConf, uint8_t, count)
DEFINE_CLASS_MSG1_H(CConfMsg_switch, uint8_t, gpio)
DEFINE_CLASS_MSG1_H(CConfMsg_watchdog, uint8_t, to)
DEFINE_CLASS_MSG3_H(CConfMsg_light, uint8_t, gpio, MacID, switchMacID, uint8_t, switchGPIO)
DEFINE_CLASS_MSG0_H(CConfMsg_reset)
DEFINE_CLASS_MSG1_H(CConfMsg_setCanBusSpeed, uint8_t, canBusSpeed)
DEFINE_CLASS_MSG1_H(CConfMsg_autoReset, uint8_t, autoResetTime)
DEFINE_CLASS_MSG0_H(CConfMsg_askForConfiguration)
DEFINE_CLASS_MSG0_H(CConfMsg_newConfiguration)
DEFINE_CLASS_MSG0_H(CTrafficMsg_ping)
DEFINE_CLASS_MSG0_H(CTrafficMsg_ImUp)


//class CTrafficMsg_fromSwitch : public CDataBase {
//public:
//	byte _gpio;
//	byte _value;
//
//	CTrafficMsg_fromSwitch(MacID macId, byte gpio, byte value);
//	CTrafficMsg_fromSwitch(byte * pDeserializeData);
//
//	byte getSize();
//	void serialize(byte * pData);
//	void deserialize(byte * pData);
//};


//class CTrafficMsg_askSwitchForData : public CDataBase {
//public:
//	byte _gpio;
//	//byte _value;
//
//	CTrafficMsg_askSwitchForData(MacID macId, byte gpio);
//	CTrafficMsg_askSwitchForData(byte * pDeserializeData);
//
//	byte getSize();
//	void serialize(byte * pData);
//	void deserialize(byte * pData);
//};


//class CConfMsg_numOfConf : public CDataBase {
//public:
//	byte _count;
//
//	//CConfDataCount();
//	CConfMsg_numOfConf(MacID macId, byte count);
//	CConfMsg_numOfConf(byte * pDeserializeData);
//
//	byte getSize();
//	void serialize(byte * pData);
//	void deserialize(byte * pData);
//};


//class CConfMsg_switch : public CDataBase {
//public:
//	byte _gpio;
//
//	CConfMsg_switch();
//	CConfMsg_switch(MacID macId, byte gpio);
//	CConfMsg_switch(byte * pDeserializeData);
//
//	byte getSize();
//	void serialize(byte * pData);
//	void deserialize(byte * pData);
//};


//class CConfMsg_light : public CDataBase {
//public:
//	byte _gpio;
//	MacID _switchMacID;
//	byte _switchGPIO;
//
//	CConfMsg_light();
//	CConfMsg_light(byte * pDeserializeData);
//	CConfMsg_light(MacID macId, byte gpio, MacID switchCanID, byte switchGPIO);
//
//	byte getSize();
//	void serialize(byte * pData);
//	void deserialize(byte * pData);
//};


//class CConfMsg_watchdog : public CDataBase {
//public :
//	uint8_t _to; //* WATCHDOG_TIMEOUT
//
//	//CConfDataWatchdog();
//	CConfMsg_watchdog(byte * pDeserializeData);
//	CConfMsg_watchdog(MacID macId, uint8_t to);
//
//	byte getSize();
//	void serialize(byte * pData);
//	void deserialize(byte * pData);
//};


//class CConfMsg_reset : public CDataBase {
//public:
//	CConfMsg_reset(MacID macId);
//	CConfMsg_reset(byte * pDeserializeData);
//
//	byte getSize();
//	void serialize(byte * pData);
//	void deserialize(byte * pData);
//};


//class CConfMsg_autoReset : public CDataBase {
//public:
//	uint8_t _autoResetTime;
//	//CConfDataAutoReset();
//	CConfMsg_autoReset(byte * pDeserializeData);
//	CConfMsg_autoReset(MacID macId, uint8_t autoResetTime);
//
//	byte getSize();
//	void serialize(byte * pData);
//	void deserialize(byte * pData);
//};



//class CConfMsg_askForConfiguration : public CDataBase {
//public:
//	CConfMsg_askForConfiguration(MacID macId);
//	CConfMsg_askForConfiguration(byte * pDeserializeData);
//
//	byte getSize();
//	void serialize(byte * pData);
//	void deserialize(byte * pData);
//};



//class CConfMsg_setCanBusSpeed : public CDataBase {
//private:
//	uint8_t _canBusSpeed;
//public:
//	CConfMsg_setCanBusSpeed(MacID macId, uint8_t canBusSpeed);
//	CConfMsg_setCanBusSpeed(byte * pDeserializeData);
//
//	byte getSize();
//	void serialize(byte * pData);
//	void deserialize(byte * pData);
//};


//class CConfMsg_newConfiguration : public CDataBase {
//private:
//public:
//	CConfMsg_newConfiguration(MacID macId);
//	CConfMsg_newConfiguration(byte * pDeserializeData);
//
//	byte getSize();
//	void serialize(byte * pData);
//	void deserialize(byte * pData);
//};


//class CTrafficMsg_ping : public CDataBase {
//public:
//	CTrafficMsg_ping(MacID macId);
//	CTrafficMsg_ping(byte * pDeserializeData);
//
//	byte getSize();
//	void serialize(byte * pData);
//	void deserialize(byte * pData);
//};


//class CTrafficMsg_ImUp : public CDataBase {
//public:
//	CTrafficMsg_ImUp(MacID macId);
//	CTrafficMsg_ImUp(byte * pDeserializeData);
//
//	byte getSize();
//	void serialize(byte * pData);
//	void deserialize(byte * pData);
//};