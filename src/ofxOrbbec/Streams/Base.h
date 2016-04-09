#pragma once

#include "ofBaseTypes.h"
#include "ofTexture.h"

#include "astra/astra.hpp"

namespace ofxOrbbec {
	class Device;

	namespace Streams {
		enum Type {
			ColorStreamType,
			DepthStreamType,
			PointStreamType
		};

		class Base : public ofBaseHasTexture, public ofBaseDraws {
		public:
			virtual Type getType() const = 0;
			virtual void update() = 0;
			bool isFrameNew();

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
			friend Device;
			virtual void newFrameArrived(astra::frame &) = 0;
			ofTexture texture;
			bool useTexture = true;

			bool hasData = false;
			bool frameNew = false;
		};

		template<typename StreamType, typename FrameType, typename PixelsType>
		class TemplateBase : public Base, public ofBaseHasPixels_<PixelsType> {
		public:
			void init(astra::stream_reader & streamReader);
			void update() override;

			float getHeight() const override;
			float getWidth() const override;

			ofPixels_<PixelsType> & getPixels() override;
			const ofPixels_<PixelsType> & getPixels() const override;
		protected:
			virtual int getNumChannels() = 0;
			void newFrameArrived(astra::frame &) override;

			StreamType * stream = nullptr;
			ofPixels_<PixelsType> pixels;

			mutex lockIncomingPixels;
			ofPixels_<PixelsType> incomingPixels;
			bool newFrameIncoming = false;
		};
	}
}