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
 * display.cpp
 *
 *  Created on: Nov 19, 2021
 *      Author: simonyu
 */

#include "common/pin.h"
#include "common/platform.h"
#include "display/display.h"
#include "utility/logger.h"

namespace pixel
{
Display::Display() : neopixel_(PlatformNeoPixel::size, Pin::neo_pixel,
NEO_GRB + NEO_KHZ800), lock_(mutex_, std::defer_lock)
{
    frame_ = std::make_shared<std::vector<Eigen::Vector3i>>();

    for (int i = 0; i < PlatformNeoPixel::size; i ++)
    {
        frame_->push_back(
                Eigen::Vector3i(PlatformNeoPixel::value_max, PlatformNeoPixel::value_max,
                        PlatformNeoPixel::value_max));
    }
}

void
Display::initialize(std::shared_ptr<Logger> logger)
{
    neopixel_.begin();
    logger_ = logger;

    clear();
    setBrightness(PlatformNeoPixel::brightness_min);
    displayStartScreen();
}

bool
Display::lock()
{
    return lock_.try_lock();
}

void
Display::unlock()
{
    lock_.unlock();
}

void
Display::setBrightness(const int& brightness)
{
    if (brightness < PlatformNeoPixel::brightness_min)
    {
        neopixel_.setBrightness(PlatformNeoPixel::brightness_min);
    }
    else if (brightness > PlatformNeoPixel::brightness_max)
    {
        neopixel_.setBrightness(PlatformNeoPixel::brightness_max);
    }
    else
    {
        neopixel_.setBrightness(brightness);
    }
}

void
Display::setFrame(std::shared_ptr<std::vector<Eigen::Vector3i>> frame)
{
    if (frame->size() != PlatformNeoPixel::size)
    {
        logger_->logError("Invalid frame size");
        return;
    }

    for (int i = 0; i < PlatformNeoPixel::size; i ++)
    {
        neopixel_.setPixelColor(i,
                neopixel_.Color(frame->at(i).x(), frame->at(i).y(), frame->at(i).z()));
    }

    neopixel_.show();
}

bool
Display::setFrameAtomic(std::shared_ptr<std::vector<Eigen::Vector3i>> frame)
{
    if (!lock())
    {
        return false;
    }

    setFrame(frame);
    unlock();

    return true;
}

void
Display::clear()
{
    lock();
    neopixel_.clear();
    neopixel_.show();
    unlock();
}

void
Display::displayStartScreen()
{
    while (!lock());

    setFrame(frame_);
    vTaskDelay(500);

    unlock();
}
}   // namespace pixel
