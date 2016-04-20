#pragma once

#include "Base.h"

namespace ofxOrbbec {
	namespace Streams {
		class Color : public TemplateBaseImage<astra::colorstream, astra::colorframe, unsigned char> {
		public:
			void init(astra::stream_reader & streamReader) override {
				TemplateBaseImage<astra::colorstream, astra::colorframe, unsigned char>::init(streamReader);
				this->stream->enable_mirroring(false);
			}
			string getTypeName() const override {
				return "Color";
			}
		protected:
			int getNumChannels() override {
				return 3;
			}
		};
	}
}