#pragma once

#include "Base.h"

namespace ofxOrbbec {
	namespace Streams {
		class Color : public TemplateBaseImage<astra::colorstream, astra::colorframe, unsigned char> {
		public:
			StreamType getType() const override {
				return StreamType::ColorStreamType;
			}
		protected:
			int getNumChannels() override {
				return 3;
			}
		};
	}
}