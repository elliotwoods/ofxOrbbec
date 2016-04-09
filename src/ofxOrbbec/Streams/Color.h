#pragma once

#include "Base.h"

namespace ofxOrbbec {
	namespace Streams {
		class Color : public TemplateBase<astra::colorstream, astra::colorframe, unsigned char> {
		public:
			Type getType() const override {
				return Type::ColorStreamType;
			}
		protected:
			int getNumChannels() override {
				return 3;
			}
		};
	}
}