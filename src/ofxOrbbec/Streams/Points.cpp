#include "Points.h"

namespace ofxOrbbec {
	namespace Streams {
		//----------
		void Points::update() {
			TemplateBaseImage<astra::pointstream, astra::pointframe, float>::update();
			const auto numVertices = this->pixels.getWidth() * this->pixels.getHeight();
			
			//safety check
			if (numVertices == 0) {
				return;
			}

			if (this->mesh.getNumVertices() != numVertices) {
				this->mesh.getVertices().resize(numVertices);
			}
			memcpy(this->mesh.getVerticesPointer(), this->pixels.getData(), numVertices * sizeof(ofVec3f));

			//stitch faces. Ignore jumps > 100mm
			const auto maxJump = 100.0f;
			this->mesh.getIndices().clear();
			auto vertices = (ofVec3f*) this->pixels.getData();

			if (this->pixels.size() >= 640 * 480) {
				for (int x = 1; x < 640; x++) {
					for (int y = 1; y < 480; y++) {
						auto topLeftIndex = (x - 1) + (y - 1) * 640;
						auto topRightIndex = (x)+(y - 1) * 640;
						auto bottomLeftIndex = (x - 1) + (y) * 640;
						auto bottomRightIndex = (x)+(y) * 640;

						auto topLeft = vertices[topLeftIndex];
						auto topRight = vertices[topRightIndex];
						auto bottomLeft = vertices[bottomLeftIndex];
						auto bottomRight = vertices[bottomRightIndex];

						//top left triangle
						{
							auto jump = max(
								max(abs(topLeft.z - topRight.z), abs(bottomLeft.z - topRight.z)),
								abs(bottomLeft.z - topRight.z));

							if (jump < maxJump) {
								this->mesh.addIndex(topRightIndex);
								this->mesh.addIndex(topLeftIndex);
								this->mesh.addIndex(bottomLeftIndex);
							}
						}

						//bottom right triangle
						{
							auto jump = max(
								max(abs(bottomRight.z - topRight.z), abs(topRight.z - bottomLeft.z)),
								abs(bottomLeft.z - bottomRight.z));

							if (jump < maxJump) {
								this->mesh.addIndex(bottomRightIndex);
								this->mesh.addIndex(topRightIndex);
								this->mesh.addIndex(bottomLeftIndex);
							}
						}
					}
				}
			}
		}

		//----------
		const ofMesh & Points::getMesh() {
			return this->mesh;
		}
	}
}