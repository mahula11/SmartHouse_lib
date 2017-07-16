

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
CTrafficMsg_fromSwitch::CTrafficMsg_fromSwitch(MacID macId, byte gpio, byte value) : CDataBase(TYPE__FROM_SWITCH, macId), _gpio(gpio), _value(value) {
}

//CTrafficDataSwitch() : CDataBase(DEVICE_TYPE_SWITCH), _gpio(0), _value(0) {};
CTrafficMsg_fromSwitch::CTrafficMsg_fromSwitch(byte * pDeserializeData) : CDataBase(TYPE__FROM_SWITCH, 0) {
	deserialize(pDeserializeData);
}

byte CTrafficMsg_fromSwitch::getSize() {
	return sizeof(_gpio) + sizeof(_value);
};

//* traffic messages doesn't send type. type is in CanID against Conf messages where we send type of message
void CTrafficMsg_fromSwitch::serialize(byte * pData) {
	*pData = _gpio;
	pData += sizeof(_gpio);
	*pData = _value;
};

//* traffic messages doesn't send type. type is in CanID against Conf messages where we send type of message
void CTrafficMsg_fromSwitch::deserialize(byte * pData) {
	_gpio = *pData;
	pData += sizeof(_gpio);
	_value = *pData;
};
//* ---------------------- end CTrafficDataSwitch --------------------------


//* ---------------------- start CTrafficDataAskSwitchForData --------------------------
CTrafficMsg_askSwitchForData::CTrafficMsg_askSwitchForData(MacID macId, byte gpio) : CDataBase(TYPE__ASK_SWITCH_FOR_VALUE, macId), _gpio(gpio) {
}

//CTrafficDataSwitch() : CDataBase(DEVICE_TYPE_SWITCH), _gpio(0), _value(0) {};
CTrafficMsg_askSwitchForData::CTrafficMsg_askSwitchForData(byte * pDeserializeData) : CDataBase(TYPE__ASK_SWITCH_FOR_VALUE, 0) {
	deserialize(pDeserializeData);
}

byte CTrafficMsg_askSwitchForData::getSize() {
	return sizeof(_gpio);
};

//* traffic messages doesn't send type. type is in CanID against Conf messages where we send type of message
void CTrafficMsg_askSwitchForData::serialize(byte * pData) {
	*pData = _gpio;
};

//* traffic messages doesn't send type. type is in CanID against Conf messages where we send type of message
void CTrafficMsg_askSwitchForData::deserialize(byte * pData) {
	_gpio = *pData;
};
//* ---------------------- end CTrafficDataAskSwitchForData --------------------------

//* ---------------------- start CConfDataCount --------------------------
CConfMsg_numOfConf::CConfMsg_numOfConf(MacID macId, byte count) : CDataBase(TYPE__FROM_CONF__COUNT, macId), _count(_count) {
}

CConfMsg_numOfConf::CConfMsg_numOfConf(byte * pDeserializeData) : CDataBase(TYPE__FROM_CONF__COUNT, 0) {
	deserialize(pDeserializeData);
};

byte CConfMsg_numOfConf::getSize() {
	return CDataBase::getSize() + sizeof(_count);
};

//* Conf messages send type against traffic messages where we don't send type
void CConfMsg_numOfConf::serialize(byte * pData) {
	if (_modeForEeprom) {
		*pData = _type;
		pData += sizeof(_type);
	}
	*pData = _count;
};

void CConfMsg_numOfConf::deserialize(byte * pData) {
	if (_modeForEeprom) {
		_type = *pData;
		pData += sizeof(_type);
	}
	_count = *pData;
};
//* ---------------------- end CConfDataCount --------------------------


//* ---------------------- start CConfDataSwitch --------------------------
CConfMsg_switch::CConfMsg_switch(MacID macId, byte gpio) : CDataBase(TYPE__FROM_CONF__SET_SIMPLE_SWITCH, macId), _gpio(gpio) {
}

CConfMsg_switch::CConfMsg_switch() : CDataBase(TYPE__FROM_CONF__SET_SIMPLE_SWITCH, 0), _gpio(0) {
}

CConfMsg_switch::CConfMsg_switch(byte * pDeserializeData) : CDataBase(TYPE__FROM_CONF__SET_SIMPLE_SWITCH, 0) {
	deserialize(pDeserializeData);
};

byte CConfMsg_switch::getSize() {
	return CDataBase::getSize() + sizeof(_gpio);
};

//* Conf messages send type against traffic messages where we don't send type
void CConfMsg_switch::serialize(byte * pData) {
	if (_modeForEeprom) {
		*pData = _type;
		pData += sizeof(_type);
	}
	*pData = _gpio;
};

void CConfMsg_switch::deserialize(byte * pData) {
	if (_modeForEeprom) {
		_type = *pData;
		pData += sizeof(_type);
	}
	_gpio = *pData;
};
//* ---------------------- end CConfDataSwitch --------------------------

//* ---------------------- start CConfDataLight --------------------------
CConfMsg_light::CConfMsg_light(MacID macId, byte gpio, MacID switchCanID, byte switchGPIO) : CDataBase(TYPE__FROM_CONF__SET_SIMPLE_LIGHT, macId), _gpio(gpio), _switchMacID(switchCanID), _switchGPIO(switchGPIO) {
}

CConfMsg_light::CConfMsg_light() : CDataBase(TYPE__FROM_CONF__SET_SIMPLE_LIGHT, 0), _gpio(0), _switchMacID(0), _switchGPIO(0) {
}

CConfMsg_light::CConfMsg_light(byte * pDeserializeData) : CDataBase(TYPE__FROM_CONF__SET_SIMPLE_LIGHT, 0) {
	deserialize(pDeserializeData);
};

byte CConfMsg_light::getSize() {
	return CDataBase::getSize() + sizeof(_gpio) + sizeof(_switchMacID) + sizeof(_switchGPIO);
};

//* Conf messages send type against traffic messages where we don't send type
void CConfMsg_light::serialize(byte * pData) {
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

void CConfMsg_light::deserialize(byte * pData) {
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
CConfMsg_watchdog::CConfMsg_watchdog(MacID macId, uint8_t to) : CDataBase(TYPE__FROM_CONF__SET_WATCHDOG_TIMEOUT, macId), _to(to) {
}

//CConfDataWatchdog::CConfDataWatchdog() : CDataBase(TYPE__FROM_CONF__SET_WATCHDOG_TIMEOUT), _to(to2000ms) {
//}

CConfMsg_watchdog::CConfMsg_watchdog(byte * pDeserializeData) : CDataBase(TYPE__FROM_CONF__SET_WATCHDOG_TIMEOUT, 0) {
	deserialize(pDeserializeData);
};

byte CConfMsg_watchdog::getSize() {
	return CDataBase::getSize() + sizeof(_to);
};

//* Conf messages send type against traffic messages where we don't send type
void CConfMsg_watchdog::serialize(byte * pData) {
	if (_modeForEeprom) {
		*pData = _type;
		pData += sizeof(_type);
	}
	*pData = _to;
};

void CConfMsg_watchdog::deserialize(byte * pData) {
	if (_modeForEeprom) {
		_type = *pData;
		pData += sizeof(_type);
	}
	_to = (WATCHDOG_TIMEOUT) *pData;
};
//* ---------------------- end CConfDataWatchdog --------------------------

//* ---------------------- start CConfDataReset --------------------------
CConfMsg_reset::CConfMsg_reset(MacID macId) : CDataBase(TYPE__FROM_CONF__RESET, macId) {
}

CConfMsg_reset::CConfMsg_reset(byte * pDeserializeData) : CDataBase(TYPE__FROM_CONF__RESET, 0) {
	deserialize(pDeserializeData);
};

byte CConfMsg_reset::getSize() {
	return CDataBase::getSize();
};

//* Conf messages send type against traffic messages where we don't send type
void CConfMsg_reset::serialize(byte * pData) {
};

void CConfMsg_reset::deserialize(byte * pData) {
};
//* ---------------------- end CConfDataReset --------------------------

//* ---------------------- start CConfDataAutoReset --------------------------
CConfMsg_autoReset::CConfMsg_autoReset(MacID macId, uint8_t autoResetTime) : CDataBase(TYPE__FROM_CONF__SET_AUTO_RESET, macId), _autoResetTime(autoResetTime) {
}

//CConfDataAutoReset::CConfDataAutoReset() : CDataBase(TYPE__FROM_CONF__SET_AUTO_RESET) {
//}

CConfMsg_autoReset::CConfMsg_autoReset(byte * pDeserializeData) : CDataBase(TYPE__FROM_CONF__SET_AUTO_RESET, 0) {
	deserialize(pDeserializeData);
};

byte CConfMsg_autoReset::getSize() {
	return CDataBase::getSize() + sizeof(_autoResetTime);
};

//* Conf messages send type against traffic messages where we don't send type
void CConfMsg_autoReset::serialize(byte * pData) {
	//CDataBase::serialize(pData);
	if (_modeForEeprom) {
		*pData = _type;
		pData += sizeof(_type);
	}
	*pData = _autoResetTime;
};

void CConfMsg_autoReset::deserialize(byte * pData) {
	if (_modeForEeprom) {
		_type = *pData;
		pData += sizeof(_type);
	}
	_autoResetTime = (WATCHDOG_TIMEOUT)*pData;
};

//* ---------------------- end CConfDataAutoReset --------------------------

//* ---------------------- start CConfMsg_askForConfiguration --------------------------
CConfMsg_askForConfiguration::CConfMsg_askForConfiguration(MacID macId) : CDataBase(TYPE__ASK_FOR_CONF, macId) {
	_destCanID.setFlagRemote();
}

CConfMsg_askForConfiguration::CConfMsg_askForConfiguration(byte * pDeserializeData) : CDataBase(TYPE__ASK_FOR_CONF, 0) {
	deserialize(pDeserializeData);
};

byte CConfMsg_askForConfiguration::getSize() {
	return CDataBase::getSize();
};

//* Conf messages send type against traffic messages where we don't send type
void CConfMsg_askForConfiguration::serialize(byte * pData) {
};

void CConfMsg_askForConfiguration::deserialize(byte * pData) {
};
//* ---------------------- end CConfDataReset --------------------------