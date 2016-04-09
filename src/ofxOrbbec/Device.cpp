#include "ofxOrbbec.h"


namespace ofxOrbbec {
	//----------
	Device::Device() {
		auto status = astra::initialize();
		if (status != ASTRA_STATUS_SUCCESS) {
			ofLogError("ofxOrbbec") << "Initialise failed with error code " << (int)status;
		}
	}

	//----------
	Device::~Device() {
		astra::terminate();
	}

	//----------
	void Device::open() {
		this->streamReader = streamSet.create_reader();
		this->streamReader.add_listener(*this);
	}

	//----------
	shared_ptr<Streams::Color> Device::initColor() {
		return this->init<Streams::Color>();
	}

	//----------
	shared_ptr<Streams::Depth> Device::initDepth() {
		return this->init<Streams::Depth>();
	}

	//----------
	shared_ptr<Streams::Points> Device::initPoints() {
		return this->init<Streams::Points>();
	}

	//----------
	shared_ptr<Streams::Skeleton> Device::initSkeleton() {
		return this->init<Streams::Skeleton>();
	}

	//----------
	void Device::update() {
		astra_temp_update();
		for (auto stream : this->streams) {
			stream->update();
		}

		//calculate device frame rate
		if (this->isFrameNew()) {
			this->incomingFrameTimes.push(chrono::high_resolution_clock::now());
			if (this->incomingFrameTimes.size() >= 2) {
				const auto duration = this->incomingFrameTimes.back() - this->incomingFrameTimes.front();
				this->frameRate = (float) this->incomingFrameTimes.size() * 1e6 / chrono::duration_cast<chrono::microseconds>(duration).count();
			}
			while (incomingFrameTimes.size() > 2) {
				incomingFrameTimes.pop();
			}
		}
	}

	//----------
	bool Device::isFrameNew() const {
		for (auto stream : this->streams) {
			if (stream->isFrameNew()) {
				return true;
			}
		}
		return false;
	}

	//----------
	float Device::getFrameRate() const {
		return this->frameRate;
	}

	//----------
	shared_ptr<Streams::Color> Device::getColor() {
		return this->get<Streams::Color>();
	}

	//----------
	shared_ptr<Streams::Depth> Device::getDepth() {
		return this->get<Streams::Depth>();
	}

	//----------
	shared_ptr<Streams::Points> Device::getPoints() {
		return this->get<Streams::Points>();
	}

	//----------
	shared_ptr<Streams::Skeleton> Device::getSkeleton() {
		return this->get<Streams::Skeleton>();
	}

	//----------
	vector<shared_ptr<Streams::Base>> Device::getStreams() {
		return this->streams;
	}

	//----------
	void Device::on_frame_ready(astra::stream_reader& reader, astra::frame& frame) {
		for (auto stream : this->streams) {
			stream->newFrameArrived(frame);
		}
	}
}
