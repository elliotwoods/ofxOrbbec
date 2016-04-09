#include "Skeleton.h"

namespace ofxOrbbec {
	namespace Streams {
		//----------
		Skeleton::Skeleton() {
			
		}

		//----------
		ofxOrbbec::Streams::StreamType Skeleton::getType() const {
			return StreamType::SkeletonStreamType;
		}

		//----------
		void Skeleton::init(astra::stream_reader & streamReader) {
			if (!ofFile::doesFileExist("../orbbec.classifier")) {
				ofLogError("ofxOrbbec::Streams::Skeleton") << "orbbec.classifier file is missing";
				return;
			}
			this->bodyTracker = make_shared<os::body_tracker>(60.0f, 49.5, 160, 120);
			this->bodyTracker->set_classifier(os::load_classifier(ofToDataPath("../orbbec.classifier").c_str()));
		}

		//----------
		void Skeleton::update() {
			this->frameNew = false;
			if (!this->bodyTracker) {
				ofLogError("ofxOrbbec::Streams::Skeleton") << "You must successfully init the skeleton tracker before calling update";
				return;
			}

			if (this->pointFrameNew) {
				this->pointFrameLock.lock();
				{
					this->bodyTracker->update(this->pointFrame);
					this->pointFrameNew = false;
				}
				this->pointFrameLock.unlock();
				this->frameNew = true;
			}
		}

		//----------
		shared_ptr<os::body_tracker> Skeleton::getBodyTracker() {
			return this->bodyTracker;
		}

		//----------
		void Skeleton::enableUpscaling(bool enabled) {
			this->bodyTracker->set_upscale_outputs(enabled);
		}

		//----------
		bool Skeleton::getUpscalingEnabled() const {
			return this->bodyTracker->upscale_outputs_enabled();
		}

		//----------
		ofPixels Skeleton::getUserMask(bool copy) const {
			return toOf(this->bodyTracker->user_mask());
		}

		//----------
		ofPixels Skeleton::getLabelsImage(bool copy) const {
			return toOf(this->bodyTracker->labels());
		}

		//----------
		void Skeleton::newFrameArrived(astra::frame & frame) {
			auto pointFrame = frame.get<astra::pointframe>();
			if (pointFrame.is_valid()) {
				this->pointFrameLock.lock();
				{
					this->pointFrame.recreate(pointFrame.resolutionX(), pointFrame.resolutionY());
					memcpy(this->pointFrame.data(), pointFrame.data(), pointFrame.byteLength());
					this->pointFrameNew = true;
				}
				this->pointFrameLock.unlock();
			}
		}
	}
}