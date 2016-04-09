#pragma once

#include <skeleton/skeleton.hpp>
#include "astra/astra.hpp"
#include "ofPixels.h"

namespace ofxOrbbec {
	template<typename PixelType>
	ofPixels_<PixelType> toOf(orbbec::skeleton::bitmap<PixelType> & bitmap) {
		ofPixels_<PixelType> pixels;
		pixels.setFromExternalPixels(bitmap.data(), bitmap.width(), bitmap.height(), bitmap.bpp() / sizeof(PixelType));
		return pixels;
	}

	template<typename PixelType>
	ofPixels_<PixelType> toOf(const orbbec::skeleton::bitmap<PixelType> & bitmap) {
		ofPixels_<PixelType> pixels;
		pixels.setFromPixels(bitmap.data(), bitmap.width(), bitmap.height(), bitmap.bpp() / sizeof(PixelType));
		return pixels;
	}
}