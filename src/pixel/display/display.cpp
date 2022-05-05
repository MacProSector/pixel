/*
 * display.cpp
 *
 *  Created on: Nov 19, 2021
 *      Author: simonyu
 */
#include "display/display.h"
#include "logger/logger.h"
#include "common/pin.h"
#include "common/platform.h"

namespace kano_pixel_kit
{
Display::Display() :
        neopixel_(static_cast<int>(PlatformNeoPixel::size), static_cast<int>(Pin::neo_pixel),
        NEO_GRB + NEO_KHZ800), lock_(mutex_, std::defer_lock), timer_start_(0), timer_end_(0)
{
    frame_ = std::make_shared<std::vector<Eigen::Vector3i>>();

    for (int i = 0; i < static_cast<int>(PlatformNeoPixel::size); i ++)
    {
        frame_->push_back(
                Eigen::Vector3i(static_cast<int>(PlatformNeoPixel::value_max),
                        static_cast<int>(PlatformNeoPixel::value_max),
                        static_cast<int>(PlatformNeoPixel::value_max)));
    }
}

void
Display::initialize(std::shared_ptr<Logger> logger)
{
    neopixel_.begin();
    logger_ = logger;

    clear();
    setBrightness(static_cast<int>(PlatformNeoPixel::brightness_min));
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
    if (brightness < static_cast<int>(PlatformNeoPixel::brightness_min))
    {
        neopixel_.setBrightness(static_cast<int>(PlatformNeoPixel::brightness_min));
    }
    else if (brightness > static_cast<int>(PlatformNeoPixel::brightness_max))
    {
        neopixel_.setBrightness(static_cast<int>(PlatformNeoPixel::brightness_max));
    }
    else
    {
        neopixel_.setBrightness(brightness);
    }
}

void
Display::setFrame(std::shared_ptr<std::vector<Eigen::Vector3i>> frame)
{
    if (frame->size() != static_cast<int>(PlatformNeoPixel::size))
    {
        logger_->logError("Invalid frame size");
        return;
    }

    for (int i = 0; i < static_cast<int>(PlatformNeoPixel::size); i ++)
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

    timer_start_ = millis();
    timer_end_ = timer_start_;

    while (timer_end_ - timer_start_ < 500)
    {
        timer_end_ = millis();
    }

    unlock();
}
} // namespace kano_pixel_kit
