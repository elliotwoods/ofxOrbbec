#pragma once

#include "Base.h"

namespace ofxOrbbec {
	namespace Streams {
		class Depth : public TemplateBaseImage<astra::depthstream, astra::depthframe, unsigned short> {
		public:
			StreamType getType() const override {
				return StreamType::DepthStreamType;
			}
		protected:
			int getNumChannels() override {
				return 1;
			}
		};
	}
}