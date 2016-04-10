#include "Depth.h"

namespace ofxOrbbec {
	namespace Streams {
		//----------
		const astra::coordinate_mapper & Depth::getCoordinateMapper() const {
			float xyz[3];
			this->stream->coordinateMapper().convert_depth_to_world(0, 0, 1000, &xyz[0], &xyz[1], &xyz[2]);
			return this->stream->coordinateMapper();
		}

		//----------
		ofVec3f Depth::depthToWorld(const ofVec3f & depthMapPosition) {
			return depthToWorld(depthMapPosition.x, depthMapPosition.y, depthMapPosition.z);
		}

		//----------
		ofVec3f Depth::depthToWorld(float x, float y, float depth) {
			ofVec3f world;
			this->getCoordinateMapper().convert_depth_to_world(x, y, depth, &world.x, &world.y, &world.z);
			return world;
		}

		//----------
		ofVec3f Depth::worldToDepth(const ofVec3f & worldPosition) {
			return this->worldToDepth(worldPosition.x, worldPosition.y, worldPosition.z);
		}

		//----------
		ofVec3f Depth::worldToDepth(float x, float y, float z) {
			ofVec3f depth;
			this->getCoordinateMapper().convert_world_to_depth(x, y, z, &depth.x, &depth.y, &depth.z);
			return depth;
		}
	}
}