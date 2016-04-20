#pragma once

#include "ofBaseTypes.h"
#include "ofTexture.h"

#include "../Converters.h"

#include "astra/astra.hpp"

namespace ofxOrbbec {
	class Device;

	namespace Streams {
		class Base {
		public:
			virtual string getTypeName() const = 0;
			virtual void init(astra::stream_reader & streamReader) = 0;
			virtual void close() = 0;
			virtual void update() = 0;
			bool isFrameNew();
		protected:
			friend Device;
			virtual void newFrameArrived(astra::frame &) = 0;
			bool hasData = false;
			bool frameNew = false;
		};

		class BaseImage : public Base, public ofBaseHasTexture, public ofBaseDraws {
		public:
			ofTexture & getTexture();
			const ofTexture & getTexture() const override;
			void setUseTexture(bool bUseTex) override;
			bool isUsingTexture() const override;

			void draw(float x, float y) const override;
			void draw(float x, float y, float w, float h) const override;
			void draw(const ofPoint &) const override;
			void draw(const ofRectangle &) const override;
			void draw(const ofPoint &, float w, float h) const override;
		protected:
			ofTexture texture;
			bool useTexture = true;
		};

		template<typename StreamType, typename FrameType, typename PixelsType>
		class TemplateBaseImage : public BaseImage, public ofBaseHasPixels_<PixelsType> {
		public:
			~TemplateBaseImage();
			void init(astra::stream_reader & streamReader) override;
			void close() override;
			virtual void update() override;

			float getHeight() const override;
			float getWidth() const override;

			ofPixels_<PixelsType> & getPixels() override;
			const ofPixels_<PixelsType> & getPixels() const override;

			StreamType getStream();
		protected:
			virtual int getNumChannels() = 0;
			void newFrameArrived(astra::frame &) override;

			unique_ptr<StreamType> stream;
			ofPixels_<PixelsType> pixels;

			mutex lockIncomingPixels;
			ofPixels_<PixelsType> incomingPixels;
			bool newFrameIncoming = false;
		};
	}
}