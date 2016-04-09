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
#ifndef ASTRA_FRAME_LISTENER_HPP
#define ASTRA_FRAME_LISTENER_HPP

namespace astra {

    class stream_reader;
    class frame;

    class frame_listener
    {
    public:
        virtual ~frame_listener() = default;
        virtual void on_frame_ready(stream_reader& reader, frame& frame) = 0;
    };

    inline bool operator==(const frame_listener& l, const frame_listener& r)
    {
        return &l == &r;
    }
}

#endif // ASTRA_FRAME_LISTENER_HPP
