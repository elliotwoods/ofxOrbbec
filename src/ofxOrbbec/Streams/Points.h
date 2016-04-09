#pragma once

#include "Base.h"

namespace ofxOrbbec {
	namespace Streams {
		class Points : public TemplateBase<astra::pointstream, astra::pointframe, float> {
		public:
			Type getType() const override {
				return Type::PointStreamType;
			}
		protected:
			int getNumChannels() override {
				return 3;
			}
		};
	}
}