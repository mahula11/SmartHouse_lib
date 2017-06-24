#include "dataTypes.h"

CDataBase::CDataBase(byte type) : _type(type) {

}

//CDataBase::CDataBase() : _type(0) {
//}

byte CDataBase::getSize() {
	return sizeof(_type);
}

byte CDataBase::getType() {
	return _type;
};

//* ---------------------- start CTrafficDataSwitch --------------------------
CTrafficDataSwitch::CTrafficDataSwitch(byte gpio, byte value) : CDataBase(DEVICE_TYPE_SWITCH), _gpio(gpio), _value(value) {
}

//CTrafficDataSwitch() : CDataBase(DEVICE_TYPE_SWITCH), _gpio(0), _value(0) {};
CTrafficDataSwitch::CTrafficDataSwitch(byte * pDeserializeData) : CDataBase(DEVICE_TYPE_SWITCH) {
	deserialize(pDeserializeData);
}

byte CTrafficDataSwitch::getSize() {
	return sizeof(_gpio) + sizeof(_value);
};

//* traffic messages doesn't send type. type is in CanID against Conf messages where we send type of message
void CTrafficDataSwitch::serialize(byte * pData) {
	*pData = _gpio;
	pData += sizeof(_gpio);
	*pData = _value;
};

//* traffic messages doesn't send type. type is in CanID against Conf messages where we send type of message
void CTrafficDataSwitch::deserialize(byte * pData) {
	_gpio = *pData;
	pData += sizeof(_gpio);
	_value = *pData;
};
//* ---------------------- end CTrafficDataSwitch --------------------------

//* ---------------------- start CConfDataSwitch --------------------------
CConfDataSwitch::CConfDataSwitch(byte gpio) : CDataBase(DEVICE_TYPE_SWITCH), _gpio(gpio) {
}

CConfDataSwitch::CConfDataSwitch() : CDataBase(DEVICE_TYPE_SWITCH), _gpio(0) {
}

CConfDataSwitch::CConfDataSwitch(byte * pDeserializeData) : CDataBase(DEVICE_TYPE_SWITCH) {
	deserialize(pDeserializeData);
};

byte CConfDataSwitch::getSize() {
	return CDataBase::getSize() + sizeof(_gpio);
};

//* Conf messages send type against traffic messages where we don't send type
void CConfDataSwitch::serialize(byte * pData) {
	*pData = _type;
	pData += sizeof(_type);
	*pData = _gpio;
};

void CConfDataSwitch::deserialize(byte * pData) {
	_type = *pData;
	pData += sizeof(_type);
	_gpio = *pData;
};
//* ---------------------- end CConfDataSwitch --------------------------

//* ---------------------- start CConfDataLight --------------------------
CConfDataLight::CConfDataLight(byte gpio, MacID switchCanID, byte switchGPIO) : CDataBase(DEVICE_TYPE_LIGHT), _gpio(gpio), _switchMacID(switchCanID), _switchGPIO(switchGPIO) {
}

CConfDataLight::CConfDataLight() : CDataBase(DEVICE_TYPE_LIGHT), _gpio(0), _switchMacID(0), _switchGPIO(0) {
}

CConfDataLight::CConfDataLight(byte * pDeserializeData) : CDataBase(DEVICE_TYPE_LIGHT) {
	deserialize(pDeserializeData);
};

byte CConfDataLight::getSize() {
	return CDataBase::getSize() + sizeof(_gpio) + sizeof(_switchMacID) + sizeof(_switchGPIO);
};

//* Conf messages send type against traffic messages where we don't send type
void CConfDataLight::serialize(byte * pData) {
	*pData = _type;
	pData += sizeof(_type);
	*pData = _gpio;
	pData += sizeof(_gpio);
	*(MacID*)pData = _switchMacID;
	pData += sizeof(_switchMacID);
	*pData = _switchGPIO;
};

void CConfDataLight::deserialize(byte * pData) {
	_type = *pData;
	pData += sizeof(_type);
	_gpio = *pData;
	pData += sizeof(_gpio);
	_switchMacID = *(MacID *)pData;
	pData += sizeof(_switchMacID);
	_switchGPIO = *pData;
};
//* ---------------------- end CConfDataLight --------------------------

//* ---------------------- start CConfDataWatchdog --------------------------
CConfDataWatchdog::CConfDataWatchdog(uint8_t to) : CDataBase(DEVICE_TYPE_WATCHDOG_TIMEOUT), _to(to) {
}

CConfDataWatchdog::CConfDataWatchdog() : CDataBase(DEVICE_TYPE_WATCHDOG_TIMEOUT), _to(to2000ms) {
}

CConfDataWatchdog::CConfDataWatchdog(byte * pDeserializeData) : CDataBase(DEVICE_TYPE_WATCHDOG_TIMEOUT) {
	deserialize(pDeserializeData);
};

byte CConfDataWatchdog::getSize() {
	return CDataBase::getSize() + sizeof(_to);
};

//* Conf messages send type against traffic messages where we don't send type
void CConfDataWatchdog::serialize(byte * pData) {
	*pData = _type;
	pData += sizeof(_type);
	*pData = _to;
};

void CConfDataWatchdog::deserialize(byte * pData) {
	_type = *pData;
	pData += sizeof(_type);
	_to = (WATCHDOG_TIMEOUT) *pData;
};
//* ---------------------- end CConfDataWatchdog --------------------------