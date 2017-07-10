#pragma once

#include <Arduino.h>

#include "dataTypes.h"



class CanID {
public:
	CanID();

private:
	bool hasFlag(byte flag1);
	bool hasFlag(byte flag1, byte flag2);
	bool hasFlag(byte flag1, byte flag2, byte flag3);

public:
	uint32_t _canID;
	
	byte getConfigPart();
	void clearConfigPart();
	void setConfigPart(byte type);

	bool hasFlag_fromSwitch();
	void setFlag_fromSwitch();
	bool hasFlag_askSwitchForValue();
	void setFlag_askSwitchForValue();
	bool hasFlag_forConfiguration();
	void setFlag_forConfiguration();

	bool hasFlag_fromConfiguration();
	//void setFlag_fromConfiguration();
	bool hasFlag_fromConfNumber();
	void setFlag_fromConfNumber();
	bool hasFlag_fromConfSetWatchdog();
	void setFlag_fromConfSetWatchdog();
	bool hasFlag_fromConfSetSwitch();
	void setFlag_fromConfSetSwitch();
	bool hasFlag_fromConfSetLight();
	void setFlag_fromConfSetLight();
	bool hasFlag_fromConfReset();
	void setFlag_fromConfReset();
	bool hasFlag_fromConfAutoResetTime();
	void setFlag_fromConfAutoResetTime();


	MacID getMacID();
	//* insert MacID to CanID
	void setMacID(MacID macID);
};

