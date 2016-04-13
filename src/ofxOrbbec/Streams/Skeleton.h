#pragma once

#include "Base.h"
#include "Points.h"
#include "../Converters.h"

#include <skeleton/skeleton.hpp>

namespace ofxOrbbec {
	namespace Streams {
		namespace os = orbbec::skeleton;

		class Skeleton : public Base {
		public:
			Skeleton();
			~Skeleton();

			string getTypeName() const override;
			void init(astra::stream_reader & streamReader) override;
			void close() override;
			void update() override;

			shared_ptr<os::body_tracker> getBodyTracker();
			void setBodyTrackerResolution(int width, int height);

			//Warning : these functions are not safe to call until you've called init...
			void enableUpscaling(bool);
			bool getUpscalingEnabled() const;

			ofPixels getUserMask(bool copy = false) const;
			ofPixels getLabelsImage(bool copy = false) const;
			ofPixels getProbabilityMap(uint8_t labelIndex, float scaleOutput = 255.0f);

			os::joint_map_type getJointsRaw() const;

			void drawSkeleton2D() const;
			void drawSkeleton3D() const;

			static const vector<pair<os::joint_type, os::joint_type>> & getBonesAtlas();
			
		protected:
			void newFrameArrived(astra::frame &) override;

			mutex pointFrameLock;

			os::bitmap_vector3f pointFrame;
			bool pointFrameNew = true;
			shared_ptr<os::body_tracker> bodyTracker;
		};
	}
}