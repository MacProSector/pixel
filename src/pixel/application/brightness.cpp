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
 * brightness.cpp
 *
 *  Created on: Nov 30, 2021
 *      Author: simonyu
 */

#include "application/brightness.h"
#include "button/button.h"
#include "button/button_state.h"
#include "common/global.h"
#include "common/platform.h"
#include "display/display.h"

namespace pixel
{
Brightness::Brightness() : color_(PlatformNeoPixel::value_max, PlatformNeoPixel::value_max, 0),
        brightness_value_(PlatformNeoPixel::brightness_min), initialized_(false)
{
    // Top horizontal leaves
    display_frame_splash_->at(PlatformNeoPixel::size / 2 - PlatformNeoPixel::width / 2 - 2) =
            color_;
    display_frame_splash_->at(PlatformNeoPixel::size / 2 - PlatformNeoPixel::width / 2 - 3) =
            color_;
    display_frame_splash_->at(PlatformNeoPixel::size / 2 - PlatformNeoPixel::width / 2 + 1) =
            color_;
    display_frame_splash_->at(PlatformNeoPixel::size / 2 - PlatformNeoPixel::width / 2 + 2) =
            color_;

    // Bottom horizontal leaves
    display_frame_splash_->at(PlatformNeoPixel::size / 2 + PlatformNeoPixel::width / 2 - 2) =
            color_;
    display_frame_splash_->at(PlatformNeoPixel::size / 2 + PlatformNeoPixel::width / 2 - 3) =
            color_;
    display_frame_splash_->at(PlatformNeoPixel::size / 2 + PlatformNeoPixel::width / 2 + 1) =
            color_;
    display_frame_splash_->at(PlatformNeoPixel::size / 2 + PlatformNeoPixel::width / 2 + 2) =
            color_;

    // Top vertical leaves
    display_frame_splash_->at(PlatformNeoPixel::width + PlatformNeoPixel::width / 2 - 1) = color_;
    display_frame_splash_->at(PlatformNeoPixel::width + PlatformNeoPixel::width / 2) = color_;
    display_frame_splash_->at(PlatformNeoPixel::width * 2 + PlatformNeoPixel::width / 2 - 1) =
            color_;
    display_frame_splash_->at(PlatformNeoPixel::width * 2 + PlatformNeoPixel::width / 2) = color_;

    // Bottom vertical leaves
    display_frame_splash_->at(
            PlatformNeoPixel::size - PlatformNeoPixel::width - PlatformNeoPixel::width / 2 - 1) =
            color_;
    display_frame_splash_->at(
            PlatformNeoPixel::size - PlatformNeoPixel::width - PlatformNeoPixel::width / 2) =
            color_;
    display_frame_splash_->at(
            PlatformNeoPixel::size - PlatformNeoPixel::width * 2 - PlatformNeoPixel::width / 2 - 1) =
            color_;
    display_frame_splash_->at(
            PlatformNeoPixel::size - PlatformNeoPixel::width * 2 - PlatformNeoPixel::width / 2) =
            color_;

    // Top diagonal leaves
    display_frame_splash_->at(PlatformNeoPixel::width + PlatformNeoPixel::width / 2 - 3) = color_;
    display_frame_splash_->at(PlatformNeoPixel::width + PlatformNeoPixel::width / 2 + 2) = color_;
    display_frame_splash_->at(PlatformNeoPixel::width * 2 + PlatformNeoPixel::width / 2 - 2) =
            color_;
    display_frame_splash_->at(PlatformNeoPixel::width * 2 + PlatformNeoPixel::width / 2 + 1) =
            color_;

    // Bottom diagonal leaves
    display_frame_splash_->at(
            PlatformNeoPixel::size - PlatformNeoPixel::width - PlatformNeoPixel::width / 2 - 3) =
            color_;
    display_frame_splash_->at(
            PlatformNeoPixel::size - PlatformNeoPixel::width - PlatformNeoPixel::width / 2 + 2) =
            color_;
    display_frame_splash_->at(
            PlatformNeoPixel::size - PlatformNeoPixel::width * 2 - PlatformNeoPixel::width / 2 - 2) =
            color_;
    display_frame_splash_->at(
            PlatformNeoPixel::size - PlatformNeoPixel::width * 2 - PlatformNeoPixel::width / 2 + 1) =
            color_;
}

void
Brightness::initialize()
{
    initialized_ = false;

    run();

    initialized_ = true;
}

void
Brightness::run()
{
    processDial();
    displayBrightness();
}

void
Brightness::processDial()
{
    static int brightness_value_last = 0;
    auto button_state = button_->getButtonState();

    brightness_value_ = PlatformNeoPixel::brightness_min
            + button_state->dial / static_cast<float>(Platform::analog_max)
                    * (PlatformNeoPixel::brightness_max - PlatformNeoPixel::brightness_min);

    if (!initialized_ || brightness_value_ != brightness_value_last)
    {
        display_->setBrightness(brightness_value_);
    }

    brightness_value_last = brightness_value_;
}

void
Brightness::displayBrightness()
{
    static int brightness_value_last = 0;

    if (!initialized_ || brightness_value_ != brightness_value_last)
    {
        int brightness_value_screen = (brightness_value_ - PlatformNeoPixel::brightness_min)
                / (static_cast<float>(PlatformNeoPixel::brightness_max)
                        - PlatformNeoPixel::brightness_min) * PlatformNeoPixel::width;

        std::fill(display_frame_->begin(), display_frame_->end(), Eigen::Vector3i(0, 0, 0));

        for (int i = 0; i < PlatformNeoPixel::size; i ++)
        {
            if (i % PlatformNeoPixel::width <= brightness_value_screen)
            {
                display_frame_->at(i) = color_;
            }
        }

        display_->setFrameAtomic(display_frame_);
    }

    brightness_value_last = brightness_value_;
}
}   // namespace pixel
