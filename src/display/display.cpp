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
Display::Display()
{
    neopixel_ = std::make_shared<Adafruit_NeoPixel>(static_cast<int>(NeoPixel::size), static_cast<int>(ESP32Pin::neo_pixel), NEO_GRB + NEO_KHZ800);
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

void
Display::lockAndSetFrame(std::shared_ptr<std::vector<Eigen::Vector3i>> frame)
{
    if (frame->size() != static_cast<int>(NeoPixel::size))
    {
        logger_->logError("Invalid frame size");
        return;
    }

    std::lock_guard<std::mutex> lock(mutex_);

    for (int i = 0; i < static_cast<int>(NeoPixel::size); i ++)
    {
        neopixel_->setPixelColor(i, neopixel_->Color(frame->at(i).x(), frame->at(i).y(), frame->at(i).z()));
    }

    neopixel_->show();
}

void
Display::clear()
{
    std::lock_guard<std::mutex> lock(mutex_);

    neopixel_->clear();
    neopixel_->show();
}
} // namespace kano_pixel_kit