/*
 * display.cpp
 *
 *  Created on: Nov 19, 2021
 *      Author: simonyu
 */
#include <Adafruit_NeoPixel.h>

#include "../devices/esp32.h"
#include "../devices/neopixel.h"
#include "../display/display.h"
#include "../logger/logger.h"

namespace kano_pixel_kit
{
Display::Display() : lock_(mutex_, std::defer_lock)
{
    neopixel_ = std::make_shared<Adafruit_NeoPixel>(static_cast<int>(NeoPixel::size), static_cast<int>(
            ESP32Pin::neo_pixel), NEO_GRB + NEO_KHZ800);
}

void
Display::initialize(std::shared_ptr<Logger> logger, const int& brightness_limit)
{
    neopixel_->begin();
    logger_ = logger;

    clear();

    if (brightness_limit >=0 && brightness_limit <= 255)
    {
        neopixel_->setBrightness(brightness_limit);
    }
    else
    {
        logger_->logError("Invalid brightness limit");
    }
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
Display::setFrame(std::shared_ptr<std::vector<Eigen::Vector3i>> frame)
{
    if (frame->size() != static_cast<int>(NeoPixel::size))
    {
        logger_->logError("Invalid frame size");
        return;
    }

    for (int i = 0; i < static_cast<int>(NeoPixel::size); i ++)
    {
        neopixel_->setPixelColor(i, neopixel_->Color(frame->at(i).x(), frame->at(i).y(), frame->at(i).z()));
    }

    neopixel_->show();
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
    neopixel_->clear();
    neopixel_->show();
    unlock();
}
} // namespace kano_pixel_kit