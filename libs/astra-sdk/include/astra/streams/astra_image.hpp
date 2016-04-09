// This file is part of the Orbbec Astra SDK [https://orbbec3d.com]
// Copyright (c) 2015 Orbbec 3D
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Be excellent to each other.
#ifndef ASTRA_IMAGE_HPP
#define ASTRA_IMAGE_HPP

#include <astra_core/astra_core.hpp>
#include <stdexcept>
#include <astra/capi/astra_ctypes.h>
#include <astra/capi/streams/image_capi.h>
#include <iostream>
#include <cstdint>

namespace astra {

    struct rgb_pixel : public astra_rgb_pixel_t
    {
        rgb_pixel()
            : rgb_pixel(0, 0, 0)
        {}

        rgb_pixel(std::uint8_t r, std::uint8_t g, std::uint8_t b)
        {
            ::astra_rgb_pixel_t::r = r;
            ::astra_rgb_pixel_t::g = g;
            ::astra_rgb_pixel_t::b = b;
        }
    };

    class imagestream_mode : private ::astra_imagestream_mode_t
    {
    public:
        imagestream_mode()
        {}

        imagestream_mode(std::uint32_t width, std::uint32_t height, std::uint8_t fps, astra_pixel_format_t format)
        {
            set_width(width);
            set_height(height);
            set_fps(fps);
            set_pixelFormat(format);
        }

        imagestream_mode(const ::astra_imagestream_mode_t& mode)
        {
            *this = mode;
        }

        imagestream_mode& operator=(const ::astra_imagestream_mode_t& mode)
        {
            set_width(mode.width);
            set_height(mode.height);
            set_fps(mode.fps);
            set_pixelFormat(mode.pixelFormat);

            return *this;
        }

        operator ::astra_imagestream_mode_t*() { return this; }
        operator const ::astra_imagestream_mode_t*() const { return this; }

        const std::uint8_t fps() const { return astra_imagestream_mode_t::fps; }
        void set_fps(std::uint8_t fps) { astra_imagestream_mode_t::fps = fps; }

        const std::uint8_t bytesPerPixel() const
        {
            std::uint8_t bpp;
            astra_pixelformat_get_bytes_per_pixel(pixelFormat(), &bpp);
            return bpp;
        }

        const std::uint32_t width() const { return astra_imagestream_mode_t::width; }
        void set_width(std::uint32_t width) { astra_imagestream_mode_t::width = width; }

        const std::uint32_t height() const { return astra_imagestream_mode_t::height; }
        void set_height(std::uint32_t height) { astra_imagestream_mode_t::height = height; }

        astra_pixel_format_t pixelFormat() const { return astra_imagestream_mode_t::pixelFormat; }
        void set_pixelFormat(astra_pixel_format_t format) { astra_imagestream_mode_t::pixelFormat = format; }

        friend std::ostream& operator<<(std::ostream& os, const imagestream_mode& ism);
    };

    inline bool operator==(const imagestream_mode& lhs, const imagestream_mode& rhs)
    {
        return
            lhs.width() == rhs.width() &&
            lhs.height() == rhs.height() &&
            lhs.pixelFormat() == rhs.pixelFormat() &&
            lhs.fps() == rhs.fps() &&
            lhs.bytesPerPixel() && rhs.bytesPerPixel();
    }

    inline bool operator!=(const imagestream_mode& lhs, const imagestream_mode& rhs)
    {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const imagestream_mode& ism)
    {
        os << ism.width()
           << "x"
           << ism.height()
           << "x"
           << static_cast<int>(ism.bytesPerPixel())
           << "@"
           << static_cast<int>(ism.fps())
           << " pf:"
           << ism.pixelFormat();

        return os;
    }

    class imagestream : public datastream
    {
    public:
        explicit imagestream(astra_streamconnection_t connection)
            : datastream(connection),
              imageStream_(reinterpret_cast<astra_imagestream_t>(connection))
        {}

        float horizontalFieldOfView()
        {
            float hFov = 0.0f;
            astra_imagestream_get_hfov(imageStream_, &hFov);

            return hFov;
        }

        float verticalFieldOfView()
        {
            float vFov = 0.0f;
            astra_imagestream_get_vfov(imageStream_, &vFov);

            return vFov;
        }

        bool mirroring_enabled()
        {
            bool mirroring = false;
            astra_imagestream_get_mirroring(imageStream_, &mirroring);

            return mirroring;
        }

        void enable_mirroring(bool mirroring)
        {
            astra_imagestream_set_mirroring(imageStream_, mirroring);
        }

        std::vector<imagestream_mode> available_modes()
        {
            astra_result_token_t token;
            std::size_t count = 0;
            astra_imagestream_request_modes(imageStream_, &token, &count);

            std::vector<imagestream_mode> result;
            result.resize(count);

            astra_imagestream_get_modes_result(imageStream_,
                                               token,
                                               reinterpret_cast<astra_imagestream_mode_t*>(&result[0]),
                                               count);

            return result;
        }

        void set_mode(const imagestream_mode& mode)
        {
            astra_imagestream_set_mode(imageStream_, mode);
        }

    private:
        astra_imagestream_t imageStream_;
    };

    template<typename TDataType, astra_stream_type_t TStreamType>
    class imageframe
    {
    public:
        imageframe(astra_imageframe_t frame, astra_pixel_format_t expected_format)
        {
            imageFrame_ = frame;
            if (imageFrame_)
            {
                astra_imageframe_get_metadata(imageFrame_, &metadata_);
                if (metadata_.pixelFormat != expected_format)
                {
                    //wrong format -- this must be an invalid frame
                    imageFrame_ = nullptr;
                    return;
                }

                astra_imageframe_get_frameindex(imageFrame_, &frameIndex_);

                void* voidData = nullptr;
                astra_imageframe_get_data_ptr(imageFrame_, &voidData, &byteLength_);
                dataPtr_ = static_cast<TDataType*>(voidData);
            }
        }

        const bool is_valid() const { return imageFrame_ != nullptr; }

        const int resolutionX() const { throwIfInvalidFrame(); return metadata_.width; }
        const int resolutionY() const { throwIfInvalidFrame(); return metadata_.height; }

        const std::uint8_t bytesPerPixel() const
        {
            throwIfInvalidFrame();

            std::uint8_t bpp;
            astra_pixelformat_get_bytes_per_pixel(metadata_.pixelFormat, &bpp);
            return bpp;
        }

        const astra_frame_index_t frameIndex() const { throwIfInvalidFrame(); return frameIndex_; }
        const astra_imageframe_t handle() const { return imageFrame_; }

        static const astra_stream_type_t streamType() { return TStreamType; }

        const TDataType* data() const { throwIfInvalidFrame(); return dataPtr_; }
        const size_t byteLength() const { throwIfInvalidFrame(); return byteLength_; }
        const size_t numberOfPixels() const { throwIfInvalidFrame(); return metadata_.width * metadata_.height; }

        void copy_to(TDataType* buffer)
        {
            throwIfInvalidFrame();
            astra_imageframe_copy_data(imageFrame_, buffer);
        }

        template<typename TFrameType>
        static TFrameType acquire(astra_reader_frame_t readerFrame,
                                  astra_stream_subtype_t subtype)
        {
            if (readerFrame != nullptr)
            {
                astra_imageframe_t imageFrame;
                astra_reader_get_imageframe(readerFrame, TStreamType, subtype, &imageFrame);

                return TFrameType(imageFrame);
            }

            return TFrameType(nullptr);
        }

    private:
        void throwIfInvalidFrame() const
        {
            if (!imageFrame_)
            {
                throw std::logic_error("Cannot operate on an invalid frame");
            }
        }

        astra_imageframe_t imageFrame_{nullptr};
        astra_image_metadata_t metadata_;
        astra_frame_index_t frameIndex_;

        TDataType* dataPtr_;

        size_t byteLength_;
    };
}

#endif // ASTRA_IMAGE_HPP
