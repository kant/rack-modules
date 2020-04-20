/* 
 * Copyright (c) 2020 Dave French <contact/dot/dave/dot/french3/at/googlemail/dot/com>
 *
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program (see COPYING); if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 *
 */

#pragma once

#include <algorithm>
#include <cmath>
#include <vector>
#include <float.h>

namespace sspo
{
    namespace AudioMath
    {
        constexpr auto LD_PI = 3.14159265358979323846264338327950288419716939937510L;
        constexpr auto k_pi = static_cast<float>(LD_PI);
        constexpr auto k_2pi = k_pi + k_pi;
        constexpr auto base_a4 = 440.0f;
        constexpr auto base_a4Midi = 69.0f;
        constexpr auto semitonesPerOctave = 12.0f;

        //* accurate to 0.032f when -5.0 < x < 5.0
        template <typename T>
        inline T fastTanh(T x)
        {
            return x * (27 + x * x) / (27 + 9 * x * x);
        }

        template <typename T>
        inline bool areSame(T a, T b, T delta = FLT_EPSILON) noexcept
        {
            return std::abs(a - b) <= delta;
        }

        template <typename T>
        inline bool areSame(const std::vector<T> &a, const std::vector<T> &b, const T delta = FLT_EPSILON)
        {
            return a.size() == b.size() ? std::equal (a.begin(), a.end(), b.begin(), [=](const T &l, const T &r) 
            -> bool 
            {
                return areSame(l, r, delta);
            })
             : false;
        }

    } // namespace AudioMath
} // namespace sspo