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
#ifndef ASTRA_HAND_HPP
#define ASTRA_HAND_HPP

#include <astra_core/astra_core.hpp>
#include <stdexcept>
#include <astra/capi/astra_ctypes.h>
#include <astra/capi/streams/hand_capi.h>
#include <astra/vector.hpp>

namespace astra {

    class handpoint : public astra_handpoint_t
    {
    public:
        handpoint(std::int32_t trackingId,
                  astra_handstatus_t status,
                  vector2i depthPosition,
                  vector3f worldPosition,
                  vector3f worldDeltaPosition)
        {
            astra_handpoint_t::trackingId = trackingId;
            astra_handpoint_t::status = status;
            astra_handpoint_t::depthPosition = depthPosition;
            astra_handpoint_t::worldPosition = worldPosition;
            astra_handpoint_t::worldDeltaPosition = worldDeltaPosition;
        }

        handpoint(const astra_handpoint_t& handPoint)
        {
            *this = handPoint;
        }

        handpoint& operator=(const ::astra_handpoint_t& handPoint)
        {
            astra_handpoint_t::trackingId = handPoint.trackingId;
            astra_handpoint_t::status = handPoint.status;
            astra_handpoint_t::depthPosition = handPoint.depthPosition;
            astra_handpoint_t::worldPosition = handPoint.worldPosition;
            astra_handpoint_t::worldDeltaPosition = handPoint.worldDeltaPosition;

            return *this;
        }

        inline operator ::astra_handpoint_t*() { return this; }
        inline operator const ::astra_handpoint_t*() const { return this; }

        inline int32_t trackingId() const { return astra_handpoint_t::trackingId; }
        inline astra_handstatus_t status() const { return astra_handpoint_t::status; }
        inline vector2i depthPosition() const { return astra_handpoint_t::depthPosition; }
        inline vector3f worldPosition() const { return astra_handpoint_t::worldPosition; }
        inline vector3f worldDeltaPosition() const { return astra_handpoint_t::worldDeltaPosition; }

    private:
        astra_handpoint_t handPoint_;
        vector2i depthPosition_;
        vector3f worldPosition_;
        vector3f worldDeltaPosition_;
    };

    using handpointList = std::vector<handpoint>;

    class handstream : public datastream
    {
    public:
        explicit handstream(astra_streamconnection_t connection)
            : datastream(connection),
              handStream_(connection)
        { }

        static const astra_stream_type_t id = ASTRA_STREAM_HAND;

        bool get_include_candidate_points()
        {
            bool includeCandidatePoints;
            astra_handstream_get_include_candidate_points(handStream_, &includeCandidatePoints);
            return includeCandidatePoints;
        }

        void set_include_candidate_points(bool includeCandidatePoints)
        {
            astra_handstream_set_include_candidate_points(handStream_, includeCandidatePoints);
        }
    private:
        astra_handstream_t handStream_;
    };

    class handframe
    {
    public:
        template<typename TFrameType>
        static TFrameType acquire(astra_reader_frame_t readerFrame,
                                  astra_stream_subtype_t subtype)
        {
            if (readerFrame != nullptr)
            {
                astra_handframe_t handFrame;
                astra_frame_get_handframe_with_subtype(readerFrame, subtype, &handFrame);
                return TFrameType(handFrame);
            }

            return TFrameType(nullptr);
        }

        handframe(astra_handframe_t handFrame)
        {
            handFrame_ = handFrame;
            if (handFrame_)
            {
                astra_handframe_get_frameindex(handFrame_, &frameIndex_);

                size_t maxHandCount;
                astra_handframe_get_hand_count(handFrame_, &maxHandCount);

                handPoints_.reserve(maxHandCount);
            }
        }

        bool is_valid() { return handFrame_ != nullptr; }
        astra_handframe_t handle() { return handFrame_; }

        size_t handpoint_count()
        {
            throwIfInvalidFrame();
            verify_handpointlist();
            return handPoints_.size();
        }

        const handpointList& handpoints()
        {
            throwIfInvalidFrame();
            verify_handpointlist();
            return handPoints_;
        }

        astra_frame_index_t frameIndex() { throwIfInvalidFrame(); return frameIndex_; }

    private:
        void throwIfInvalidFrame()
        {
            if (handFrame_ == nullptr)
            {
                throw std::logic_error("Cannot operate on an invalid frame");
            }
        }

        void verify_handpointlist()
        {
            if (handPointsInitialized_)
            {
                return;
            }

            handPointsInitialized_ = true;

            astra_handpoint_t* handPtr;
            size_t maxHandCount;

            astra_handframe_get_shared_hand_array(handFrame_, &handPtr, &maxHandCount);

            for (size_t i = 0; i < maxHandCount; ++i, ++handPtr)
            {
                astra_handpoint_t& p = *handPtr;
                if (p.status != astra_handstatus_t::HAND_STATUS_NOTTRACKING)
                {
                    handPoints_.push_back(handpoint(p));
                }
            }
        }

        bool handPointsInitialized_{ false };
        handpointList handPoints_;
        astra_handframe_t handFrame_{nullptr};
        astra_frame_index_t frameIndex_;
    };
}

#endif /* ASTRA_HAND_HPP */
