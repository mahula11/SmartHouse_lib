

#include "dataTypes.h"


//* ---------------------- start CDataBase --------------------------

CDataBase::CDataBase(byte type, MacID macId) : _type(type), _modeForEeprom(false) {
	_destCanID.setMacID(macId);
	_destCanID.setFlagExtended();
	_destCanID.setType(type);
}

//CDataBase::CDataBase() : _type(0) {
//}

byte CDataBase::getSize() {
	return _modeForEeprom ? sizeof(_type) : 0;
}

byte CDataBase::getType() {
	return _type;
};

void CDataBase::setModeForEeprom(bool mode) {
	_modeForEeprom = mode;
}

//void CDataBase::sendMsg() {
//	byte data[8];
//	serialize(data);
//	INT8U ret = CAN0.sendMsgBuf(canId, 1, cdb.getSize(), data);
//#ifdef DEBUG_BUILD
//	if (ret == CAN_OK) {
//		DEBUG(F("Send msg CanID:") << canId << ",deviceType:" << cdb.getType());
//	} else {
//		DEBUG(F("Failure when send CanID:") << canId << F(",error:") << ret);
//	}
//#endif
//}
//* ---------------------- end CDataBase --------------------------

//* ---------------------- start CTrafficDataSwitch --------------------------
CTrafficDataSwitch::CTrafficDataSwitch(MacID macId, byte gpio, byte value) : CDataBase(TYPE__FROM_SWITCH, macId), _gpio(gpio), _value(value) {
}

//CTrafficDataSwitch() : CDataBase(DEVICE_TYPE_SWITCH), _gpio(0), _value(0) {};
CTrafficDataSwitch::CTrafficDataSwitch(byte * pDeserializeData) : CDataBase(TYPE__FROM_SWITCH, 0) {
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


//* ---------------------- start CTrafficDataAskSwitchForData --------------------------
CTrafficDataAskSwitchForData::CTrafficDataAskSwitchForData(MacID macId, byte gpio) : CDataBase(TYPE__ASK_SWITCH_FOR_VALUE, macId), _gpio(gpio) {
}

//CTrafficDataSwitch() : CDataBase(DEVICE_TYPE_SWITCH), _gpio(0), _value(0) {};
CTrafficDataAskSwitchForData::CTrafficDataAskSwitchForData(byte * pDeserializeData) : CDataBase(TYPE__ASK_SWITCH_FOR_VALUE, 0) {
	deserialize(pDeserializeData);
}

byte CTrafficDataAskSwitchForData::getSize() {
	return sizeof(_gpio);
};

//* traffic messages doesn't send type. type is in CanID against Conf messages where we send type of message
void CTrafficDataAskSwitchForData::serialize(byte * pData) {
	*pData = _gpio;
};

//* traffic messages doesn't send type. type is in CanID against Conf messages where we send type of message
void CTrafficDataAskSwitchForData::deserialize(byte * pData) {
	_gpio = *pData;
};
//* ---------------------- end CTrafficDataAskSwitchForData --------------------------

//* ---------------------- start CConfDataCount --------------------------
CConfDataCount::CConfDataCount(MacID macId, byte count) : CDataBase(TYPE__FROM_CONF__COUNT, macId), _count(_count) {
}

CConfDataCount::CConfDataCount(byte * pDeserializeData) : CDataBase(TYPE__FROM_CONF__COUNT, 0) {
	deserialize(pDeserializeData);
};

byte CConfDataCount::getSize() {
	return CDataBase::getSize() + sizeof(_count);
};

//* Conf messages send type against traffic messages where we don't send type
void CConfDataCount::serialize(byte * pData) {
	if (_modeForEeprom) {
		*pData = _type;
		pData += sizeof(_type);
	}
	*pData = _count;
};

void CConfDataCount::deserialize(byte * pData) {
	if (_modeForEeprom) {
		_type = *pData;
		pData += sizeof(_type);
	}
	_count = *pData;
};
//* ---------------------- end CConfDataCount --------------------------


//* ---------------------- start CConfDataSwitch --------------------------
CConfDataSwitch::CConfDataSwitch(MacID macId, byte gpio) : CDataBase(TYPE__FROM_CONF__SET_SIMPLE_SWITCH, macId), _gpio(gpio) {
}

CConfDataSwitch::CConfDataSwitch() : CDataBase(TYPE__FROM_CONF__SET_SIMPLE_SWITCH, 0), _gpio(0) {
}

CConfDataSwitch::CConfDataSwitch(byte * pDeserializeData) : CDataBase(TYPE__FROM_CONF__SET_SIMPLE_SWITCH, 0) {
	deserialize(pDeserializeData);
};

byte CConfDataSwitch::getSize() {
	return CDataBase::getSize() + sizeof(_gpio);
};

//* Conf messages send type against traffic messages where we don't send type
void CConfDataSwitch::serialize(byte * pData) {
	if (_modeForEeprom) {
		*pData = _type;
		pData += sizeof(_type);
	}
	*pData = _gpio;
};

void CConfDataSwitch::deserialize(byte * pData) {
	if (_modeForEeprom) {
		_type = *pData;
		pData += sizeof(_type);
	}
	_gpio = *pData;
};
//* ---------------------- end CConfDataSwitch --------------------------

//* ---------------------- start CConfDataLight --------------------------
CConfDataLight::CConfDataLight(MacID macId, byte gpio, MacID switchCanID, byte switchGPIO) : CDataBase(TYPE__FROM_CONF__SET_SIMPLE_LIGHT, macId), _gpio(gpio), _switchMacID(switchCanID), _switchGPIO(switchGPIO) {
}

CConfDataLight::CConfDataLight() : CDataBase(TYPE__FROM_CONF__SET_SIMPLE_LIGHT, 0), _gpio(0), _switchMacID(0), _switchGPIO(0) {
}

CConfDataLight::CConfDataLight(byte * pDeserializeData) : CDataBase(TYPE__FROM_CONF__SET_SIMPLE_LIGHT, 0) {
	deserialize(pDeserializeData);
};

byte CConfDataLight::getSize() {
	return CDataBase::getSize() + sizeof(_gpio) + sizeof(_switchMacID) + sizeof(_switchGPIO);
};

//* Conf messages send type against traffic messages where we don't send type
void CConfDataLight::serialize(byte * pData) {
	if (_modeForEeprom) {
		*pData = _type;
		pData += sizeof(_type);
	}
	*pData = _gpio;
	pData += sizeof(_gpio);
	*(MacID*)pData = _switchMacID;
	pData += sizeof(_switchMacID);
	*pData = _switchGPIO;
};

void CConfDataLight::deserialize(byte * pData) {
	if (_modeForEeprom) {
		_type = *pData;
		pData += sizeof(_type);
	}
	_gpio = *pData;
	pData += sizeof(_gpio);
	_switchMacID = *(MacID *)pData;
	pData += sizeof(_switchMacID);
	_switchGPIO = *pData;
};
//* ---------------------- end CConfDataLight --------------------------

//* ---------------------- start CConfDataWatchdog --------------------------
CConfDataWatchdog::CConfDataWatchdog(MacID macId, uint8_t to) : CDataBase(TYPE__FROM_CONF__SET_WATCHDOG_TIMEOUT, macId), _to(to) {
}

//CConfDataWatchdog::CConfDataWatchdog() : CDataBase(TYPE__FROM_CONF__SET_WATCHDOG_TIMEOUT), _to(to2000ms) {
//}

CConfDataWatchdog::CConfDataWatchdog(byte * pDeserializeData) : CDataBase(TYPE__FROM_CONF__SET_WATCHDOG_TIMEOUT, 0) {
	deserialize(pDeserializeData);
};

byte CConfDataWatchdog::getSize() {
	return CDataBase::getSize() + sizeof(_to);
};

//* Conf messages send type against traffic messages where we don't send type
void CConfDataWatchdog::serialize(byte * pData) {
	if (_modeForEeprom) {
		*pData = _type;
		pData += sizeof(_type);
	}
	*pData = _to;
};

void CConfDataWatchdog::deserialize(byte * pData) {
	if (_modeForEeprom) {
		_type = *pData;
		pData += sizeof(_type);
	}
	_to = (WATCHDOG_TIMEOUT) *pData;
};
//* ---------------------- end CConfDataWatchdog --------------------------

//* ---------------------- start CConfDataReset --------------------------
CConfDataReset::CConfDataReset(MacID macId) : CDataBase(TYPE__FROM_CONF__RESET, macId) {
}

CConfDataReset::CConfDataReset(byte * pDeserializeData) : CDataBase(TYPE__FROM_CONF__RESET, 0) {
	deserialize(pDeserializeData);
};

byte CConfDataReset::getSize() {
	return CDataBase::getSize();
};

//* Conf messages send type against traffic messages where we don't send type
void CConfDataReset::serialize(byte * pData) {
};

void CConfDataReset::deserialize(byte * pData) {
};
//* ---------------------- end CConfDataReset --------------------------

//* ---------------------- start CConfDataAutoReset --------------------------
CConfDataAutoReset::CConfDataAutoReset(MacID macId, uint8_t autoResetTime) : CDataBase(TYPE__FROM_CONF__SET_AUTO_RESET, macId), _autoResetTime(autoResetTime) {
}

//CConfDataAutoReset::CConfDataAutoReset() : CDataBase(TYPE__FROM_CONF__SET_AUTO_RESET) {
//}

CConfDataAutoReset::CConfDataAutoReset(byte * pDeserializeData) : CDataBase(TYPE__FROM_CONF__SET_AUTO_RESET, 0) {
	deserialize(pDeserializeData);
};

byte CConfDataAutoReset::getSize() {
	return CDataBase::getSize() + sizeof(_autoResetTime);
};

//* Conf messages send type against traffic messages where we don't send type
void CConfDataAutoReset::serialize(byte * pData) {
	//CDataBase::serialize(pData);
	if (_modeForEeprom) {
		*pData = _type;
		pData += sizeof(_type);
	}
	*pData = _autoResetTime;
};

void CConfDataAutoReset::deserialize(byte * pData) {
	if (_modeForEeprom) {
		_type = *pData;
		pData += sizeof(_type);
	}
	_autoResetTime = (WATCHDOG_TIMEOUT)*pData;
};

//* ---------------------- end CConfDataAutoReset --------------------------