/*
 * kano_pixel_kit.ino
 *
 *  Created on: Nov 19, 2021
 *      Author: simonyu
 */
#include "src/devices/neopixel.h"
#include "src/display/display.h"
#include "src/logger/logger.h"

using kano_pixel_kit::Display;
using kano_pixel_kit::Logger;
using kano_pixel_kit::NeoPixel;

std::shared_ptr<Display> display_;
std::shared_ptr<Logger> logger_;

void setup()
{
    display_ = std::make_shared<Display>();
    logger_ = std::make_shared<Logger>(&Serial);

    logger_->initialize();
    display_->initialize(logger_);

    std::vector<Eigen::Vector3i> frame;

    for (int i = 0; i < static_cast<int>(NeoPixel::size); i ++)
    {
        frame.push_back(Eigen::Vector3i(10, 10, 10));
    }

    display_->setFrame(frame);
}

void loop()
{
}
