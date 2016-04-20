#pragma once

#include "Base.h"

namespace ofxOrbbec {
	namespace Streams {
		class Depth : public TemplateBaseImage<astra::depthstream, astra::depthframe, unsigned short> {
		public:
			void init(astra::stream_reader & streamReader) override {
				TemplateBaseImage<astra::depthstream, astra::depthframe, unsigned short>::init(streamReader);
				this->stream->enable_mirroring(false);
			}

			string getTypeName() const override {
				return "Depth";
			}

			const astra::coordinate_mapper & getCoordinateMapper() const;

			ofVec3f depthToWorld(const ofVec3f & depthMapPosition);
			ofVec3f depthToWorld(float x, float y, float depth);

			ofVec3f worldToDepth(const ofVec3f & worldPosition);
			ofVec3f worldToDepth(float x, float y, float z);
		protected:
			int getNumChannels() override {
				return 1;
			}
		};
	}
}