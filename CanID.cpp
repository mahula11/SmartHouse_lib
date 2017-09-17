#include "CanID.h"
#include "dataTypes.h"


CanID::CanID() {
	_canID = 0;
}

CanID::CanID(MacID macID) {
	_canID = macID; //* macID is first 16bits from _canID
}

byte CanID::getConfigPart() {
	//* nastavime masku 16711680 = 0000 0000 ‭1111 1111 0000 0000 0000 0000‬
	//* posunieme o 16 miest do prava, cize posunieme bity do prveho byte 
	return (_canID & 16711680) >> 16;
}

void CanID::clearConfigPart() {
	//* resetne prvych 16 bitov, aby sa mohla nastavit MacID
	//* 4294901760 = 1111 1111 1111 1111 0000 0000 0000 0000
	//* ‭‭4278255615‬ = 1111 1111 0000 0000 1111 1111 1111 1111‬
	_canID &= 4278255615;
	//_canID &= ‭4294901760;
}

void CanID::setConfigPart(byte type) {
	bitSet(_canID, 31);				//* set extended message
	_canID += ((uint32_t)type << 16);
}

bool CanID::hasFlag(byte flag1) {
	if (getConfigPart() == flag1) { // || res == CANID_MSGTYPE_ADD_CONF || res == CANID_MSGTYPE_DEL_CONF) {
		return true;
	} else {
		return false;
	}
}

bool CanID::hasFlag(byte flag1, byte flag2) {
	byte res = getConfigPart();
	if (res == flag1 || res == flag2) { // || res == CANID_MSGTYPE_DEL_CONF) {
		return true;
	} else {
		return false;
	}
}

bool CanID::hasFlag(byte flag1, byte flag2, byte flag3) {
	byte res = getConfigPart();
	if (res == flag1 || res == flag2 || res == flag3) {
		return true;
	} else {
		return false;
	}
}

MacID CanID::getMacID() {
	//* vycisti IDcko od bitov, ktore su konfiguracne, ktore nie su pre identifikator
	//* 65535 = 0000 0000 0000 0000 1111 1111 1111 1111
	return _canID & 65535;
}

//* insert MacID to CanID
void CanID::setMacID(MacID macID) {
	//* resetne prvych 16 bitov, aby sa mohla nastavit MacID
	//* 4294901760 = 1111 1111 1111 1111 0000 0000 0000 0000
	_canID &= 4294901760;
	//* do vycistenej casti pripocitame 16bitove cislo
	_canID += macID;
}

void CanID::setFlagExtended() {
	bitSet(_canID, 31);				//* set extended message
}

void CanID::setFlagRemote() {
	bitSet(_canID, 30);				//* set remote flag
}

void CanID::setType(uint8_t type) {
	_canID += ((uint32_t)type << 16);
}





bool CanID::hasFlag_fromSwitch() {
	return hasFlag(TYPE__FROM_SWITCH);
}

//void CanID::setFlag_fromSwitch() {
//	bitSet(_canID, 31);				//* set extended message
//	//* v tomto pripade posunieme 16x 5tku do lava, dostaneme ju do casti, kde mame konfiguraciu
//	//* 0101 --> 0101 0000 0000 0000 0000
//	//* CanBus ID je hodnota od 0 do 16bitov
//	//* cize ked tieto hodnoty spocitame (logicky OR), tak budeme mat konfiguraciu s IDckom
//	_canID += ((uint32_t)TYPE__FROM_SWITCH << 16);
//}

bool CanID::hasFlag_askSwitchForValue() {
	return hasFlag(TYPE__ASK_SWITCH_FOR_VALUE);
}

bool CanID::hasFlag_ping() {
	return hasFlag(TYPE__FROM_ANY_DEVICE__PING);
}

bool CanID::hasFlag_ImUp() {
	return hasFlag(TYPE__FROM_ANY_DEVICE__IM_UP);
}

//void CanID::setFlag_askSwitchForValue() {
//	bitSet(_canID, 31);				//* set extended message
//	_canID += ((uint32_t)TYPE__ASK_SWITCH_FOR_VALUE << 16);
//}

bool CanID::hasFlag_forConfiguration() {
	return hasFlag(TYPE__ASK_FOR_CONF);
}




//void CanID::setFlag_forConfiguration() {
//	bitSet(_canID, 31);				//* set extended message
//	bitSet(_canID, 30);				//* set remote flag
//	_canID += ((uint32_t)TYPE__ASK_FOR_CONF << 16);
//}

bool CanID::hasFlag_fromConfiguration() {
	byte i = 0;
	while (idsFromConf[i] != 0) {
		if (hasFlag(idsFromConf[i++])) {
			return true;
		}
	}
	return false;
}

bool CanID::hasFlag_fromConfNumber() {
	return hasFlag(TYPE__FROM_CONF__COUNT);
}

//void CanID::setFlag_fromConfNumber() {
//	bitSet(_canID, 31);				//* set extended message
//	_canID += ((uint32_t)TYPE__FROM_CONF__COUNT << 16);
//}

bool CanID::hasFlag_fromConfSetWatchdog() {
	return hasFlag(TYPE__FROM_CONF__SET_WATCHDOG_TIMEOUT);
}

bool CanID::hasFlag_fromConfSetCanBusSpeed() {
	return hasFlag(TYPE__FROM_CONF__SET_CANBUS_SPEED);
}


//void CanID::setFlag_fromConfSetWatchdog() {
//	bitSet(_canID, 31);				//* set extended message
//	_canID += ((uint32_t)TYPE__FROM_CONF__SET_WATCHDOG_TIMEOUT << 16);
//}

bool CanID::hasFlag_fromConfSetSwitch() {
	return hasFlag(TYPE__FROM_CONF__SET_SIMPLE_SWITCH);
}

//void CanID::setFlag_fromConfSetSwitch() {
//	bitSet(_canID, 31);				//* set extended message
//	_canID += ((uint32_t)TYPE__FROM_CONF__SET_SIMPLE_SWITCH << 16);
//}

bool CanID::hasFlag_fromConfSetLight() {
	return hasFlag(TYPE__FROM_CONF__SET_SIMPLE_LIGHT);
}

//void CanID::setFlag_fromConfSetLight() {
//	bitSet(_canID, 31);				//* set extended message
//	_canID += ((uint32_t)TYPE__FROM_CONF__SET_SIMPLE_LIGHT << 16);
//}

bool CanID::hasFlag_fromConfReset() {
	return hasFlag(TYPE__FROM_CONF__RESET);
}

//void CanID::setFlag_fromConfReset() {
//	bitSet(_canID, 31);				//* set extended message
//	_canID += ((uint32_t)TYPE__FROM_CONF__RESET << 16);
//}

bool CanID::hasFlag_fromConfAutoResetTime() {
	return hasFlag(TYPE__FROM_CONF__SET_AUTO_RESET);
}

//void CanID::setFlag_fromConfAutoResetTime() {
//	bitSet(_canID, 31);				//* set extended message
//	_canID += ((uint32_t)TYPE__FROM_CONF__SET_AUTO_RESET << 16);
//}



