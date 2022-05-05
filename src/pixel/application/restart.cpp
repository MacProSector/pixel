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
 * restart.cpp
 *
 *  Created on: Nov 20, 2021
 *      Author: simonyu
 */

#include <Arduino.h>

#include "common/platform.h"
#include "application/restart.h"

namespace kano_pixel_kit
{
Restart::Restart(std::shared_ptr<Button> button, std::shared_ptr<Display> display,
        std::shared_ptr<Logger> logger) : Application(button, display, logger),
        timer_started_(false), timer_start_(0), timer_end_(0)
{
}

void
Restart::initialize()
{
    button_state_ = button_->getState();
    display_frame_->clear();

    for (int i = 0; i < PlatformNeoPixel::size; i ++)
    {
        display_frame_->push_back(Eigen::Vector3i(PlatformNeoPixel::value_max, 0, 0));
    }
}

void
Restart::run()
{
    button_state_ = button_->getState();

    if (button_state_->joystick_click)
    {
        if (!timer_started_)
        {
            timer_started_ = true;
            timer_start_ = millis();
        }

        timer_end_ = millis();
    }
    else
    {
        timer_started_ = false;
        timer_start_ = millis();
        timer_end_ = timer_start_;
    }

    if (timer_end_ - timer_start_ > 5000)
    {
        logger_->logInfo("Restarting..");
        displayRestartScreen();
        ESP.restart();
    }
}

void
Restart::displayRestartScreen()
{
    while (!display_->lock());
    display_->setFrame(display_frame_);

    timer_start_ = millis();
    timer_end_ = timer_start_;

    while (timer_end_ - timer_start_ < 500)
    {
        timer_end_ = millis();
    }
}
} // namespace kano_pixel_kit
