#pragma once

#include "Base.h"

namespace ofxOrbbec {
	namespace Streams {
		class Depth : public TemplateBaseImage<astra::depthstream, astra::depthframe, unsigned short> {
		public:
			string getTypeName() const override {
				return "Depth";
			}
		protected:
			int getNumChannels() override {
				return 1;
			}
		};
	}
}