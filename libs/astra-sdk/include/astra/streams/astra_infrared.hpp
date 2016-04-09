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
#ifndef ASTRA_INFRARED_HPP
#define ASTRA_INFRARED_HPP

#include <astra_core/astra_core.hpp>
#include <astra/capi/astra_ctypes.h>
#include <astra/capi/streams/infrared_capi.h>
#include <astra/streams/astra_image.hpp>
#include <astra/vector.hpp>

namespace astra {

    class infraredstream : public imagestream
    {
    public:
        explicit infraredstream(astra_streamconnection_t connection)
            : imagestream(connection)
        { }

        static const astra_stream_type_t id = ASTRA_STREAM_INFRARED;
    };

    class infraredframe_16 : public imageframe<uint16_t, ASTRA_STREAM_INFRARED>
    {
    public:
        infraredframe_16(astra_imageframe_t frame)
            : imageframe(frame, ASTRA_PIXEL_FORMAT_GRAY16)
        {}
    };

    class infraredframe_rgb : public imageframe<rgb_pixel, ASTRA_STREAM_INFRARED>
    {
    public:
        infraredframe_rgb(astra_imageframe_t frame)
            : imageframe(frame, ASTRA_PIXEL_FORMAT_RGB888)
        {}
    };

}

#endif /* ASTRA_INFRARED_HPP */
