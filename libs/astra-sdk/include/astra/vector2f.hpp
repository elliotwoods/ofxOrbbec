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
#ifndef VECTOR2F_H
#define VECTOR2F_H

#include <cmath>
#include "capi/astra_ctypes.h"

namespace astra
{
    struct vector2f : public astra_vector2f_t
    {
        vector2f()
        {
            this->x = 0.0f;
            this->y = 0.0f;
        }

        vector2f(const astra_vector2f_t& v)
        {
            *this = v;
        }

        vector2f& operator=(const astra_vector2f_t& rhs)
        {
            ::astra_vector2f_t::x = rhs.x;
            ::astra_vector2f_t::y = rhs.y;

            return *this;
        }

        vector2f(float x, float y)
        {
            this->x = x;
            this->y = y;
        }

        inline operator ::astra_vector2f_t*() { return this; }
        inline operator const ::astra_vector2f_t*() const { return this; }

        float length() const;
        float length_squared() const;
        float dot(const vector2f& v) const;

        static vector2f normalize(vector2f v);

        static inline vector2f zero();
        inline bool is_zero() const;

        friend bool operator==(const vector2f& lhs, const vector2f& rhs);
        friend vector2f operator+(const vector2f& lhs, const vector2f& rhs);
        friend vector2f operator-(const vector2f& lhs, const vector2f& rhs);
        friend vector2f operator*(const vector2f& lhs, const float& rhs);
        friend vector2f operator*(const float& lhs, const vector2f& rhs);
        friend vector2f operator/(const vector2f& lhs, const float& rhs);

        vector2f operator-();
        vector2f& operator+=(const vector2f& rhs);
        vector2f& operator-=(const vector2f& rhs);
        vector2f& operator*=(const float& rhs);
        vector2f& operator/=(const float& rhs);
    };

    inline vector2f vector2f::normalize(vector2f v)
    {
        double length = std::sqrt(v.x*v.x + v.y*v.y);

        if (length < 1e-9)
        {
            return vector2f(0.0f, 0.0f);
        }
        else
        {
            return vector2f(
                static_cast<float>(v.x / length),
                static_cast<float>(v.y / length));
        }
    }

    inline float vector2f::length() const
    {
        return std::sqrt(x * x + y * y);
    }

    inline float vector2f::length_squared() const
    {
        return x * x + y * y;
    }

    inline float vector2f::dot(const vector2f& v) const
    {
        return x * v.x + y * v.y;
    }

    inline vector2f& vector2f::operator+=(const vector2f& rhs)
    {
        this->x = this->x + rhs.x;
        this->y = this->y + rhs.y;
        return *this;
    }

    inline vector2f& vector2f::operator-=(const vector2f& rhs)
    {
        this->x = this->x - rhs.x;
        this->y = this->y - rhs.y;
        return *this;
    }

    inline vector2f& vector2f::operator*=(const float& rhs)
    {
        this->x = this->x * rhs;
        this->y = this->y * rhs;
        return *this;
    }

    inline vector2f& vector2f::operator/=(const float& rhs)
    {
        this->x = this->x / rhs;
        this->y = this->y / rhs;
        return *this;
    }

    inline vector2f vector2f::operator-()
    {
        return vector2f(-this->x, -this->y);
    }

    inline bool operator==(const vector2f& lhs, const vector2f& rhs)
    {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }

    inline bool operator!=(const vector2f& lhs, const vector2f& rhs)
    {
        return !(lhs == rhs);
    }

    inline vector2f operator+(const vector2f& lhs, const vector2f& rhs)
    {
        return vector2f(lhs.x + rhs.x, lhs.y + rhs.y);
    }

    inline vector2f operator-(const vector2f& lhs, const vector2f& rhs)
    {
        return vector2f(lhs.x - rhs.x, lhs.y - rhs.y);
    }

    inline vector2f operator*(const vector2f& lhs, const float& rhs)
    {
        return vector2f(lhs.x * rhs, lhs.y * rhs);
    }

    inline vector2f operator*(const float& lhs, const vector2f& rhs)
    {
        return rhs * lhs;
    }

    inline vector2f operator/(const vector2f& lhs, const float& rhs)
    {
        return vector2f(lhs.x / rhs, lhs.y / rhs);
    }

    inline vector2f vector2f::zero()
    {
        vector2f zero;
        return zero;
    }

    inline bool vector2f::is_zero() const
    {
        return *this == zero();
    }

}

#endif // VECTOR2F_H
