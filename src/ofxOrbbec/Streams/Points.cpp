#include "Points.h"

namespace ofxOrbbec {
	namespace Streams {
		//----------
		void Points::update() {
			TemplateBaseImage<astra::pointstream, astra::pointframe, float>::update();
			const auto numVertices = this->pixels.getWidth() * this->pixels.getHeight();
			if (this->mesh.getNumVertices() != numVertices) {
				this->mesh.getVertices().resize(numVertices);
			}
			memcpy(this->mesh.getVerticesPointer(), this->pixels.getData(), numVertices * sizeof(ofVec3f));
		}

		//----------
		const ofMesh & Points::getMesh() {
			return this->mesh;
		}
	}
}