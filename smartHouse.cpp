#include "smartHouse.h"

//CONF * SmartHouse::newConf(byte count) {
//	return newConf(count, 0);
//}

CONF * SmartHouse::newConf(byte count) {//, MacID macAddress) {
	CONF * conf = new CONF;
	//conf->count = count;
	//conf->macAddress = macAddress;
	conf->ppConfData = new CDataBase*[count];
	return conf;
}