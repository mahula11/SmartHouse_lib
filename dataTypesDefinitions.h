#pragma once



#define DEFINE_CLASS_REMOTE_MSG0_CPP(className, messageType)		\
	className::className(MacID macId) : CDataBase(messageType, macId) { \
		_destCanID.setFlagRemote(); \
	} \
 \
	className::className(byte * pDeserializeData) : CDataBase(messageType, 0) { \
		deserialize(pDeserializeData); \
	}; \
 \
	byte className::getSize() { \
		return CDataBase::getSize(); \
	}; \
 \
	void className::serialize(byte * pData) { \
	}; \
 \
	void className::deserialize(byte * pData) { \
	};

//* ----------------------------------------------------------------------------------------------------------------------------
#define DEFINE_CLASS_MSG0_H(className)		\
	class className : public CDataBase {	\
	public:									\
		className(MacID macId);				\
		className(byte * pDeserializeData); \
		byte getSize();						\
		static bool isMatch(CanID &canID);  \
		void serialize(byte * pData);		\
		void deserialize(byte * pData);		\
	}; 

#define DEFINE_CLASS_MSG0_CPP(className, messageType)							\
	className::className(MacID macId) : CDataBase(messageType, macId) {			\
	}																			\
																				\
	className::className(byte * pDeserializeData) : CDataBase(messageType, 0) { \
		deserialize(pDeserializeData);											\
	};																			\
																				\
	bool className::isMatch(CanID &canID) {									\
		return messageType == canID.getType();									\
	}																			\
																				\
	byte className::getSize() {													\
		return CDataBase::getSize();											\
	}; 																			\
																				\
	void className::serialize(byte * pData) {									\
		if (_modeForEeprom) {													\
			*pData = _type;														\
			pData += sizeof(_type);												\
		}																		\
	}; 																			\
 																				\
	void className::deserialize(byte * pData) { 								\
		if (_modeForEeprom) { 													\
			_type = *pData; 													\
			pData += sizeof(_type); 											\
		} 																		\
	};
//* ----------------------------------------------------------------------------------------------------------------------------

#define DEFINE_CLASS_MSG1_H(className, varType, varName)	\
	class className : public CDataBase {					\
	public:													\
		varType _##varName;									\
		className();										\
		className(MacID macId, varType varName);			\
		className(byte * pDeserializeData);					\
		byte getSize();										\
		static bool isMatch(CanID &canID);					\
		void serialize(byte * pData);						\
		void deserialize(byte * pData);						\
	}; 


#define DEFINE_CLASS_MSG1_CPP(className, messageType, varType, varName)											\
	className::className() : CDataBase(messageType, 0) {														\
		_##varName = 0;																							\
	}																											\
																												\
	className::className(MacID macId, varType varName) : CDataBase(messageType, macId), _##varName(varName) {	\
	}																											\
																												\
	className::className(byte * pDeserializeData) : CDataBase(messageType, 0) {									\
		deserialize(pDeserializeData);																			\
	}																											\
																												\
	bool className::isMatch(CanID &canID) {																	\
		return messageType == canID.getType();																						\
	}																											\
																												\
	byte className::getSize() {																					\
		return CDataBase::getSize() + sizeof(_##varName);														\
	}																											\
																												\
	void className::serialize(byte * pData) {																	\
		if (_modeForEeprom) {																					\
			*pData = _type;																						\
			pData += sizeof(_type);																				\
		}																										\
		*pData = _##varName;																						\
	} 																											\
																												\
	void className::deserialize(byte * pData) {																	\
		if (_modeForEeprom) { 																					\
			_type = *pData; 																					\
			pData += sizeof(_type); 																			\
		} 																										\
		_##varName = *pData; 																						\
	}

//* ----------------------------------------------------------------------------------------------------------------------------

#define DEFINE_CLASS_MSG2_H(className, varType1, varName1, varType2, varName2)	\
	class className : public CDataBase {					\
	public:													\
		varType1 _##varName1;								\
		varType2 _##varName2;								\
		className();										\
		className(MacID macId, varType1 varName1, varType2 varName2);	\
		className(byte * pDeserializeData);					\
		static bool isMatch(CanID &canID);							\
		byte getSize();										\
		void serialize(byte * pData);						\
		void deserialize(byte * pData);						\
	}; 

#define DEFINE_CLASS_MSG2_CPP(className, messageType, varType1, varName1, varType2, varName2)					\
	className::className(MacID macId, varType1 varName1, varType2 varName2) : CDataBase(messageType, macId) {	\
		_##varName1 = varName1;																					\
		_##varName2 = varName2;																					\
	}																											\
																												\
	className::className() : CDataBase(messageType, 0) {														\
		_##varName1 = 0;																							\
		_##varName2 = 0;																							\
	}																											\
																												\
	className::className(byte * pDeserializeData) : CDataBase(messageType, 0) {									\
		deserialize(pDeserializeData);																			\
	}																											\
																												\
	bool className::isMatch(CanID &canID) {																	\
		return messageType == canID.getType();																						\
	}																											\
																												\
	byte className::getSize() {																					\
		return CDataBase::getSize() + sizeof(_##varName1) + sizeof(_##varName2);									\
	}																											\
																												\
	void className::serialize(byte * pData) {																	\
		if (_modeForEeprom) {																					\
			*pData = _type;																						\
			pData += sizeof(_type);																				\
		}																										\
		*pData = _##varName1;																						\
		pData += sizeof(_##varName1);																				\
		*pData = _##varName2;																						\
	} 																											\
																												\
	void className::deserialize(byte * pData) {																	\
		if (_modeForEeprom) { 																					\
			_type = *pData; 																					\
			pData += sizeof(_type); 																			\
		} 																										\
		_##varName1 = *pData; 																					\
		pData += sizeof(_##varName1); 																			\
		_##varName2 = *(MacID *)pData; 																			\
	}

//* ----------------------------------------------------------------------------------------------------------------------------

#define DEFINE_CLASS_MSG3_H(className, varType1, varName1, varType2, varName2, varType3, varName3)	\
	class className : public CDataBase {															\
	public:																							\
		varType1 _##varName1;																		\
		varType2 _##varName2;																		\
		varType3 _##varName3;																		\
		className();																				\
		className(MacID macId, varType1 varName1, varType2 varName2, varType3 varName3);			\
		className(byte * pDeserializeData);															\
		static bool isMatch(CanID &canID);															\
		byte getSize();																				\
		void serialize(byte * pData);																\
		void deserialize(byte * pData);																\
	}; 

#define DEFINE_CLASS_MSG3_CPP(className, messageType, varType1, varName1, varType2, varName2, varType3, varName3)					\
	className::className(MacID macId, varType1 varName1, varType2 varName2, varType3 varName3) : CDataBase(messageType, macId) {	\
		_##varName1 = varName1;																					\
		_##varName2 = varName2;																					\
		_##varName3 = varName3;																					\
	}																											\
																												\
	className::className() : CDataBase(messageType, 0) {														\
		_##varName1 = 0;																						\
		_##varName2 = 0;																						\
		_##varName3 = 0;																						\
	}																											\
																												\
	className::className(byte * pDeserializeData) : CDataBase(messageType, 0) {									\
		deserialize(pDeserializeData);																			\
	}																											\
																												\
	bool className::isMatch(CanID &canID) {																		\
		return messageType == canID.getType();																	\
	}																											\
																												\
	byte className::getSize() {																					\
		return CDataBase::getSize() + sizeof(_##varName1) + sizeof(_##varName2) + sizeof(_##varName3);			\
	}																											\
																												\
	void className::serialize(byte * pData) {																	\
		if (_modeForEeprom) {																					\
			*pData = _type;																						\
			pData += sizeof(_type);																				\
		}																										\
		*pData = _##varName1;																						\
		pData += sizeof(_##varName1);																				\
		*pData = _##varName2;																						\
		pData += sizeof(_##varName2);																				\
		*pData = _##varName3;																						\
	} 																											\
																												\
	void className::deserialize(byte * pData) {																	\
		if (_modeForEeprom) { 																					\
			_type = *pData; 																					\
			pData += sizeof(_type); 																			\
		} 																										\
		_##varName1 = *pData; 																					\
		pData += sizeof(_##varName1); 																			\
		_##varName2 = *(MacID *)pData; 																			\
		pData += sizeof(_##varName2); 																			\
		_##varName3 = *pData; 																					\
	}

//* ----------------------------------------------------------------------------------------------------------------------------