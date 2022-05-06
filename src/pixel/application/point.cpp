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
 * point.cpp
 *
 *  Created on: Nov 20, 2021
 *      Author: simonyu
 */

#include "application/point.h"
#include "button/button.h"
#include "button/button_state.h"
#include "common/global.h"
#include "common/platform.h"
#include "display/display.h"

namespace pixel
{
Point::Point() : color_dial_(Eigen::Vector3i(0, 0, PlatformNeoPixel::value_max)),
        color_buttons_(Eigen::Vector3i(PlatformNeoPixel::value_max, 0, 0)), pixel_index_dial_(0),
        pixel_index_buttons_(0), set_display_frame_(false)
{
    // Dial point with fading trail
    display_frame_splash_->at(PlatformNeoPixel::size / 3 + 2) = (color_dial_.cast<float>() * 0.4)
            .cast<int>();
    display_frame_splash_->at(PlatformNeoPixel::size / 3 + 1) = (color_dial_.cast<float>() * 0.6)
            .cast<int>();
    display_frame_splash_->at(PlatformNeoPixel::size / 3) = (color_dial_.cast<float>() * 0.8)
            .cast<int>();
    display_frame_splash_->at(PlatformNeoPixel::size / 3 - 1) = color_dial_;

    // Button point with fading trail
    display_frame_splash_->at(PlatformNeoPixel::size / 3 * 2 - 1) = (color_buttons_.cast<float>()
            * 0.4).cast<int>();
    display_frame_splash_->at(PlatformNeoPixel::size / 3 * 2) = (color_buttons_.cast<float>() * 0.6)
            .cast<int>();
    display_frame_splash_->at(PlatformNeoPixel::size / 3 * 2 + 1) = (color_buttons_.cast<float>()
            * 0.8).cast<int>();
    display_frame_splash_->at(PlatformNeoPixel::size / 3 * 2 + 2) = color_buttons_;
}

void
Point::initialize()
{
    auto button_state = button_->getButtonState();

    pixel_index_dial_ = button_state->dial / static_cast<float>(Platform::analog_max)
            * (PlatformNeoPixel::size - 1);
    display_frame_->at(pixel_index_dial_) = color_dial_;
    display_frame_->at(pixel_index_buttons_) = color_buttons_;

    display_->setFrameAtomic(display_frame_);
}

void
Point::run()
{
    set_display_frame_ = false;

    processDial();
    processJoystick();
    processPushbutton();

    if (set_display_frame_)
    {
        std::fill(display_frame_->begin(), display_frame_->end(), Eigen::Vector3i(0, 0, 0));

        display_frame_->at(pixel_index_dial_) = color_dial_;
        display_frame_->at(pixel_index_buttons_) = color_buttons_;

        display_->setFrameAtomic(display_frame_);
    }
}

void
Point::processDial()
{
    static int pixel_index_dial_last = 0;
    auto button_state = button_->getButtonState();

    pixel_index_dial_ = button_state->dial / static_cast<float>(Platform::analog_max)
            * (PlatformNeoPixel::size - 1);

    if (pixel_index_dial_ != pixel_index_dial_last)
    {
        set_display_frame_ = true;
    }

    pixel_index_dial_last = pixel_index_dial_;
}

void
Point::processJoystick()
{
    auto button_state = button_->getButtonState();

    if (button_state->joystick_up && pixel_index_buttons_ >= PlatformNeoPixel::width)
    {
        pixel_index_buttons_ -= PlatformNeoPixel::width;
        set_display_frame_ = true;
    }

    if (button_state->joystick_down
            && pixel_index_buttons_ < PlatformNeoPixel::size - PlatformNeoPixel::width)
    {
        pixel_index_buttons_ += PlatformNeoPixel::width;
        set_display_frame_ = true;
    }

    if (button_state->joystick_left && pixel_index_buttons_ % PlatformNeoPixel::width > 0)
    {
        pixel_index_buttons_ --;
        set_display_frame_ = true;
    }

    if (button_state->joystick_right
            && pixel_index_buttons_ % PlatformNeoPixel::width < PlatformNeoPixel::width - 1)
    {
        pixel_index_buttons_ ++;
        set_display_frame_ = true;
    }
}

void
Point::processPushbutton()
{
    auto button_state = button_->getButtonState();

    if (button_state->pushbutton_left && pixel_index_buttons_ > 0)
    {
        pixel_index_buttons_ --;
        set_display_frame_ = true;
    }

    if (button_state->pushbutton_right && pixel_index_buttons_ < PlatformNeoPixel::size - 1)
    {
        pixel_index_buttons_ ++;
        set_display_frame_ = true;
    }
}
}   // namespace pixel
