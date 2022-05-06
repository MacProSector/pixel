/*
 *  Copyright (C) 2022  Simon Yu
 *
 *  Developed by:   Simon Yu (yujunda@icloud.com)
 *                  https://www.simonyu.net/
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

/*
 * application.cpp
 *
 *  Created on: Nov 30, 2021
 *      Author: simonyu
 */

#include "application/application.h"
#include "common/platform.h"

namespace pixel
{
Application::Application()
{
    display_frame_ = std::make_shared<std::vector<Eigen::Vector3i>>();
    display_frame_splash_ = std::make_shared<std::vector<Eigen::Vector3i>>();

    for (int i = 0; i < PlatformNeoPixel::size; i ++)
    {
        display_frame_->push_back(Eigen::Vector3i(0, 0, 0));
    }

    for (int i = 0; i < PlatformNeoPixel::size; i ++)
    {
        // Default white border
        if (i < PlatformNeoPixel::width || i > PlatformNeoPixel::size - PlatformNeoPixel::width
                || i % PlatformNeoPixel::width == 0
                || i % PlatformNeoPixel::width == PlatformNeoPixel::width - 1)
        {
            display_frame_splash_->push_back(
                    Eigen::Vector3i(PlatformNeoPixel::value_max, PlatformNeoPixel::value_max,
                            PlatformNeoPixel::value_max));
        }
        else
        {
            display_frame_splash_->push_back(Eigen::Vector3i(0, 0, 0));
        }
    }
}

std::shared_ptr<std::vector<Eigen::Vector3i>>
Application::getSplashScreen() const
{
    return display_frame_splash_;
}
}   // namespace pixel
