#pragma once

#include "Streams/Base.h"
#include "Streams/Color.h"
#include "Streams/Depth.h"
#include "Streams/Infrared.h"
#include "Streams/Points.h"
#include "Streams/Skeleton.h"

#include "astra/astra.hpp"

#include <vector>
#include <memory>

namespace ofxOrbbec {
	class Device : public astra::frame_listener {
	public:
		Device();
		~Device();

		void open();

		template<typename StreamType>
		shared_ptr<StreamType> init() {
			//check it doesn't already exist
			{
				auto existingStream = this->get<StreamType>(false);
				if (existingStream) {
					ofLogWarning("ofxOrbbec") << "Stream of type " << typeid(StreamType).name() << "already exists";
					return existingStream;
				}
			}

			//if not make it
			{
				auto stream = make_shared<StreamType>();
				stream->init(this->streamReader);
				this->streams.push_back(stream);
				return stream;
			}
		}
		shared_ptr<Streams::Color> initColor();
		shared_ptr<Streams::Depth> initDepth();
		shared_ptr<Streams::Infrared> initInfrared();
		shared_ptr<Streams::Points> initPoints();
		shared_ptr<Streams::Skeleton> initSkeleton();
		
		template<typename StreamType>
		bool has() {
			for (auto stream : this->streams) {
				if (dynamic_pointer_cast<StreamType>(stream)) {
					return true;
				}
			}
			return false;
		}

		template<typename StreamType>
		void close() {
			for (auto it = this->streams.begin(); it != this->streams.end(); ) {
				auto typedStream = dynamic_pointer_cast<StreamType>(*it);
				if (typedStream) {
					it->reset();
					it = this->streams.erase(it);
				}
				else {
					it++;
				}
			}
		}
		void closeColor();
		void closeDepth();
		void closeInfrared();
		void closePoints();
		void closeSkeleton();

		void update();
		bool isFrameNew() const;
		float getFrameRate() const;

		template<typename StreamType>
		shared_ptr<StreamType> get(bool complain = true) {
			for (auto stream : this->streams) {
				auto typedStream = dynamic_pointer_cast<StreamType>(stream);
				if (typedStream) {
					return typedStream;
				}
			}
			if (complain) {
				ofLogError("ofxOrbbec") << "Stream of type " << typeid(StreamType).name() << " is not available. Please initialise it first.";
			}
			return shared_ptr<StreamType>();
		}

		shared_ptr<Streams::Color> getColor();
		shared_ptr<Streams::Depth> getDepth();
		shared_ptr<Streams::Infrared> getInfrared();
		shared_ptr<Streams::Points> getPoints();
		shared_ptr<Streams::Skeleton> getSkeleton();
		vector<shared_ptr<Streams::Base>> getStreams();

	protected:
		void on_frame_ready(astra::stream_reader& reader, astra::frame& frame) override;

		astra::streamset streamSet;
		astra::stream_reader streamReader;
		std::vector<std::shared_ptr<Streams::Base>> streams;
	
		queue<chrono::high_resolution_clock::time_point> incomingFrameTimes;
		float frameRate = 0.0f;
	};
}
