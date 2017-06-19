#pragma once

#include <Arduino.h>

#include "dataTypes.h"

class CCanID {
public:
	CCanID();

private:
	byte getConfigPart();
	bool hasFlag(byte flag1);
	bool hasFlag(byte flag1, byte flag2);
	bool hasFlag(byte flag1, byte flag2, byte flag3);

public:
	uint32_t _canID;

	bool hasFlag_fromSwitch();
	void setFlag_fromSwitch();
	bool hasFlag_askSwitchForValue();
	void setFlag_askSwitchForValue();
	bool hasFlag_forConfiguration();
	void setFlag_forConfiguration();
	bool hasFlag_fromConfiguration();
	void setFlag_fromConfiguration();
	MacID getMacID();
	//* insert MacID to CanID
	void setMacID(MacID macID);
};

