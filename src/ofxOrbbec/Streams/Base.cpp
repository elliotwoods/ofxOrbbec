#include "Base.h"

namespace ofxOrbbec {
	namespace Streams {
#pragma mark Base
		//----------
		bool Base::isFrameNew() {
			return this->frameNew;
		}

		//----------
		ofTexture & Base::getTexture() {
			return this->texture;
		}

		//----------
		const ofTexture & Base::getTexture() const {
			return this->texture;
		}

		//----------
		void Base::setUseTexture(bool bUseTex) {
			this->useTexture = bUseTex;
		}

		//----------
		bool Base::isUsingTexture() const {
			return this->useTexture;
		}

		//----------
		void Base::draw(float x, float y) const {
			ofBaseDraws::draw(x, y);
		}

		//----------
		void Base::draw(float x, float y, float w, float h) const {
			if (this->hasData) {
				this->texture.draw(x, y, w, h);
			}
		}

		//----------
		void Base::draw(const ofPoint & point) const {
			ofBaseDraws::draw(point);
		}

		//----------
		void Base::draw(const ofRectangle & rectangle) const {
			ofBaseDraws::draw(rectangle);
		}

		//----------
		void Base::draw(const ofPoint & point, float w, float h) const {
			ofBaseDraws::draw(point, w, h);
		}

#pragma mark TemplateBase
		//----------
		template<typename StreamType, typename FrameType, typename PixelsType>
		void TemplateBase<StreamType, FrameType, PixelsType>::init(astra::stream_reader & streamReader) {
			this->stream = &streamReader.stream<StreamType>();
			this->stream->start();
		}

		//----------
		template<typename StreamType, typename FrameType, typename PixelsType>
		void TemplateBase<StreamType, FrameType, PixelsType>::update() {
			if (this->newFrameIncoming) {
				this->lockIncomingPixels.lock();
				{
					swap(this->pixels, this->incomingPixels);
					this->newFrameIncoming = false;
				}
				this->lockIncomingPixels.unlock();

				if (this->useTexture) {
					this->texture.loadData(this->pixels);
				}
				this->frameNew = true;
				this->hasData = true;
			}
			else {
				this->frameNew = false;
			}
		}
		
		//----------
		template<typename StreamType, typename FrameType, typename PixelsType>
		float TemplateBase<StreamType, FrameType, PixelsType>::getHeight() const {
			return this->pixels.getHeight();
		}

		//----------
		template<typename StreamType, typename FrameType, typename PixelsType>
		float TemplateBase<StreamType, FrameType, PixelsType>::getWidth() const {
			return this->pixels.getWidth();
		}

		//----------
		template<typename StreamType, typename FrameType, typename PixelsType>
		ofPixels_<PixelsType> & TemplateBase<StreamType, FrameType, PixelsType>::getPixels() {
			return this->pixels;
		}

		//----------
		template<typename StreamType, typename FrameType, typename PixelsType>
		const ofPixels_<PixelsType> & TemplateBase<StreamType, FrameType, PixelsType>::getPixels() const {
			return this->pixels;
		}

		//----------
		template<typename StreamType, typename FrameType, typename PixelsType>
		void TemplateBase<StreamType, FrameType, PixelsType>::newFrameArrived(astra::frame & frame) {
			auto ourFrame = frame.get<FrameType>();
			if (ourFrame.is_valid()) {
				this->lockIncomingPixels.lock();
				{
					this->incomingPixels.setFromPixels((PixelsType*)ourFrame.data(), ourFrame.resolutionX(), ourFrame.resolutionY(), this->getNumChannels());
					this->newFrameIncoming = true;
				}
				this->lockIncomingPixels.unlock();
			}
		}

		//---------
		template class TemplateBase<astra::colorstream, astra::colorframe, unsigned char>;
		template class TemplateBase<astra::depthstream, astra::depthframe, unsigned short>;
		template class TemplateBase<astra::pointstream, astra::pointframe, float>;
	}
}