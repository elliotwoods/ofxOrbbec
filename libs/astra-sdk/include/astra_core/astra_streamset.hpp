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
#ifndef ASTRA_STREAMSET_HPP
#define ASTRA_STREAMSET_HPP

#include <string>
#include "capi/astra_core.h"
#include "astra_stream_reader.hpp"
#include <stdexcept>

namespace astra {

    static const char* ASTRA_DEFAULT_DEVICE_URI = "device/default";

    class streamset
    {
    public:
        streamset()
            : streamset(ASTRA_DEFAULT_DEVICE_URI)
        {}

        streamset(const char* uri)
        {
            setRef_ = std::make_shared<streamset_ref>(uri);
        }

        streamset(const streamset& other)
            : setRef_(other.setRef_)
        {}

        streamset& operator=(const streamset& rhs)
        {
            this->setRef_ = rhs.setRef_;
            return *this;
        }

        bool is_valid() { return setRef_ != nullptr; }

        inline stream_reader create_reader();
        astra_streamsetconnection_t get_handle() const { return setRef_->connection_handle(); }

    private:
        class streamset_ref;
        using streamset_ref_ptr = std::shared_ptr<streamset_ref>;

        class streamset_ref :
            public std::enable_shared_from_this<streamset_ref>
        {
        public:
            streamset_ref(std::string uri)
                :  uri_(uri)
            { }

            void connect()
            {
                if (!is_connected())
                    astra_streamset_open(uri_.c_str(), &connection_);
            }

            bool is_connected() { return connection_ != nullptr; }

            ~streamset_ref()
            {
                if (is_connected())
                    astra_streamset_close(&connection_);
            }

            astra_streamsetconnection_t connection_handle() const { return connection_; }

        private:
            astra_streamsetconnection_t connection_{nullptr};
            std::string uri_;
        };

        streamset_ref_ptr setRef_;

        friend bool operator==(const streamset& lhs, const streamset& rhs);
        friend bool operator!=(const streamset& lhs, const streamset& rhs);
    };

    inline bool operator==(const streamset& lhs, const streamset& rhs)
    {
        return lhs.setRef_ == rhs.setRef_;
    }

    inline bool operator!=(const streamset& lhs, const streamset& rhs)
    {
        return !(lhs == rhs);
    }

    stream_reader streamset::create_reader()
    {
        if (!setRef_->is_connected())
            setRef_->connect();

        astra_reader_t reader;
        astra_reader_create(get_handle(), &reader);

        return stream_reader(reader);
    }
}

#endif // ASTRA_STREAMSET_HPP
