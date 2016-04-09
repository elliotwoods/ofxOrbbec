#pragma once

#include "Base.h"

namespace ofxOrbbec {
	namespace Streams {
		class Depth : public TemplateBase<astra::depthstream, astra::depthframe, unsigned short> {
		public:
			Type getType() const override {
				return Type::DepthStreamType;
			}
		protected:
			int getNumChannels() override {
				return 1;
			}
		};
	}
}