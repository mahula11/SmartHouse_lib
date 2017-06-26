#include "CanID.h"


CCanID::CCanID() {
	_canID = 0;
}

byte CCanID::getConfigPart() {
	//* nastavime masku 16711680 = 0000 0000 ‭1111 1111 0000 0000 0000 0000‬
	//* posunieme o 16 miest do prava, cize posunieme bity do prveho byte 
	return (_canID & 16711680) >> 16;
}

bool CCanID::hasFlag(byte flag1) {
	if (getConfigPart() == flag1) { // || res == CANID_MSGTYPE_ADD_CONF || res == CANID_MSGTYPE_DEL_CONF) {
		return true;
	} else {
		return false;
	}
}

bool CCanID::hasFlag(byte flag1, byte flag2) {
	byte res = getConfigPart();
	if (res == flag1 || res == flag2) { // || res == CANID_MSGTYPE_DEL_CONF) {
		return true;
	} else {
		return false;
	}
}

bool CCanID::hasFlag(byte flag1, byte flag2, byte flag3) {
	byte res = getConfigPart();
	if (res == flag1 || res == flag2 || res == flag3) {
		return true;
	} else {
		return false;
	}
}

bool CCanID::hasFlag_fromSwitch() {
	return hasFlag(MSGTYPE_SWITCH_SEND);
}

void CCanID::setFlag_fromSwitch() {
	bitSet(_canID, 31);				//* set extended message
	//* v tomto pripade posunieme 16x 5tku do lava, dostaneme ju do casti, kde mame konfiguraciu
	//* 0101 --> 0101 0000 0000 0000 0000
	//* CanBus ID je hodnota od 0 do 16bitov
	//* cize ked tieto hodnoty spocitame (logicky OR), tak budeme mat konfiguraciu s IDckom
	_canID += ((uint32_t)MSGTYPE_SWITCH_SEND << 16);
}

bool CCanID::hasFlag_askSwitchForValue() {
	return hasFlag(MSGTYPE_ASK_SWITCH_FOR_VALUE);
}

void CCanID::setFlag_askSwitchForValue() {
	bitSet(_canID, 31);				//* set extended message
	_canID += ((uint32_t)MSGTYPE_ASK_SWITCH_FOR_VALUE << 16);
}

bool CCanID::hasFlag_forConfiguration() {
	return hasFlag(MSGTYPE_FOR_CANCONF);
}

void CCanID::setFlag_forConfiguration() {
	bitSet(_canID, 31);				//* set extended message
	bitSet(_canID, 30);				//* set remote flag
	_canID += ((uint32_t)MSGTYPE_FOR_CANCONF << 16);
}

bool CCanID::hasFlag_fromConfiguration() {
	return hasFlag(MSGTYPE_FROM_CANCONF, MSGTYPE_FROM_CANCONF_ADD, MSGTYPE_FROM_CANCONF_DEL);
}

void CCanID::setFlag_fromConfiguration() {
	bitSet(_canID, 31);				//* set extended message
	_canID += ((uint32_t)MSGTYPE_FROM_CANCONF << 16);
}

bool CCanID::hasFlag_fromConfSetWatchdog() {

}

void CCanID::setFlag_fromConfSetWatchdog() {

}

void CCanID::hasFlag_fromConfSetSwitch() {

}

void CCanID::setFlag_fromConfSetSwitch() {

}

void CCanID::hasFlag_fromConfSetLight() {

}

void CCanID::setFlag_fromConfSetLight() {

}


MacID CCanID::getMacID() {
	//* vycisti IDcko od bitov, ktore su konfiguracne, ktore nie su pre identifikator
	//* 65535 = 0000 0000 0000 0000 1111 1111 1111 1111
	return _canID & 65535;
}

//* insert MacID to CanID
void CCanID::setMacID(MacID macID) {
	//* resetne prvych 16 bitov, aby sa mohla nastavit MacID
	//* 4294901760 = 1111 1111 1111 1111 0000 0000 0000 0000
	_canID &= 4294901760;
	//* do vycistenej casti pripocitame 16bitove cislo
	_canID += macID;
}