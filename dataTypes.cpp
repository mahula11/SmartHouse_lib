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

byte CDataBase::getType(byte * pData) {
	return *pData;
};

//*---------------------------------------------

CTrafficDataSwitch::CTrafficDataSwitch(byte gpio, byte value) : CDataBase(DEVICE_TYPE_SWITCH), _gpio(gpio), _value(value) {
}

//CTrafficDataSwitch() : CDataBase(DEVICE_TYPE_SWITCH), _gpio(0), _value(0) {};
CTrafficDataSwitch::CTrafficDataSwitch(byte * pDeserializeData) : CDataBase(DEVICE_TYPE_SWITCH) {
	deserialize(pDeserializeData);
}

byte CTrafficDataSwitch::getSize() {
	return CDataBase::getSize() + sizeof(_gpio) + sizeof(_value);
};

void CTrafficDataSwitch::serialize(byte * pData) {
	*pData = _type;
	pData += sizeof(_type);
	*pData = _gpio;
	pData += sizeof(_gpio);
	*pData = _value;
};

void CTrafficDataSwitch::deserialize(byte * pData) {
	_type = *pData;
	pData += sizeof(_type);
	_gpio = *pData;
	pData += sizeof(_gpio);
	_value = *pData;
};


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

