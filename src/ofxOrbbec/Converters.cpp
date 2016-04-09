#include "Converters.h"
#define OFXORBBEC_MATCHED_TYPE_BODY(OFTYPE, ORBBECTYPE) \
	OFTYPE & toOf(ORBBECTYPE & x) { \
		return *(OFTYPE*)(&x); \
	} \
	const OFTYPE & toOf(const ORBBECTYPE & x) { \
		return *(const OFTYPE*)(&x); \
	} \
	ORBBECTYPE & toOrbbec(OFTYPE & x) { \
		return *(ORBBECTYPE*)(&x); \
	} \
	const ORBBECTYPE & toOrbbec(const OFTYPE & x) { \
		return *(ORBBECTYPE*)(&x); \
	}

namespace ofxOrbbec {
	OFXORBBEC_MATCHED_TYPE_BODY(ofVec3f, os::vector3f);
}
