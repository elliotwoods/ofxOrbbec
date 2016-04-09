#pragma once


#include <skeleton/skeleton.hpp>
#include "astra/astra.hpp"
#include "ofPixels.h"

namespace ofxOrbbec {
	namespace os = orbbec::skeleton;
	template<typename PixelType>
	ofPixels_<PixelType> toOf(os::bitmap<PixelType> & bitmap) {
		ofPixels_<PixelType> pixels;
		pixels.setFromExternalPixels(bitmap.data(), bitmap.width(), bitmap.height(), bitmap.bpp() / sizeof(PixelType));
		return pixels;
	}

	template<typename PixelType>
	ofPixels_<PixelType> toOf(const os::bitmap<PixelType> & bitmap) {
		ofPixels_<PixelType> pixels;
		pixels.setFromPixels(bitmap.data(), bitmap.width(), bitmap.height(), bitmap.bpp() / sizeof(PixelType));
		return pixels;
	}

#define OFXORBBEC_MATCHED_TYPE_HEADER(OFTYPE, ORBBECTYPE) \
	OFTYPE & toOf(ORBBECTYPE & x); \
	const OFTYPE & toOf(const ORBBECTYPE & x); \
	ORBBECTYPE & toOrbbec(OFTYPE & x); \
	const ORBBECTYPE & toOrbbec(const OFTYPE & x);

	OFXORBBEC_MATCHED_TYPE_HEADER(ofVec3f, os::vector3f);
}