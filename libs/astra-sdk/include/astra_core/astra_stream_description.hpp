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
#ifndef ASTRA_STREAM_DESCRIPTION_HPP
#define ASTRA_STREAM_DESCRIPTION_HPP

#include "capi/astra_core.h"
#include <cassert>

namespace astra {

    class stream_description : private ::astra_stream_desc_t
    {
    public:
        stream_description(::astra_stream_type_t type,
                           ::astra_stream_subtype_t subtype = DEFAULT_SUBTYPE)
        {
            ::astra_stream_desc_t::type = type;
            ::astra_stream_desc_t::subtype = subtype;
        }

        stream_description(const ::astra_stream_desc_t& desc)
        {
            *this = desc;
        }

        stream_description& operator=(const ::astra_stream_desc_t& desc)
        {
            ::astra_stream_desc_t::type = desc.type;
            ::astra_stream_desc_t::subtype = desc.subtype;

            return *this;
        }

        operator ::astra_stream_desc_t*() { return this; }
        operator const ::astra_stream_desc_t*() const { return this; }

        astra_stream_type_t type() const { return ::astra_stream_desc_t::type; }
        void set_type(astra_stream_type_t type) { ::astra_stream_desc_t::type = type; }

        astra_stream_subtype_t subtype() const { return ::astra_stream_desc_t::subtype; }
        void set_subtype(astra_stream_subtype_t subtype) { ::astra_stream_desc_t::subtype = subtype; }
    };

    inline bool operator==(const stream_description& lhs, const stream_description& rhs)
    {
        return lhs.type() == rhs.type() && lhs.subtype() == rhs.subtype();
    }

    inline bool operator!=(const stream_description& lhs, const stream_description& rhs)
    {
        return !(lhs == rhs);
    }
}

#endif // ASTRA_STREAM_DESCRIPTION_HPP
