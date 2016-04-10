#pragma once

#include "Base.h"

namespace ofxOrbbec {
	namespace Streams {
		class Infrared : public TemplateBaseImage<astra::infraredstream, astra::infraredframe_16, unsigned short> {
		public:
			string getTypeName() const override {
				return "Infrared";
			}
			void init(astra::stream_reader & streamReader) override;

		protected:
			int getNumChannels() override {
				return 1;
			}
		};
	}
}