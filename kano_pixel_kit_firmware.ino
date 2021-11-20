/*
 * kano_pixel_kit.ino
 *
 *  Created on: Nov 19, 2021
 *      Author: simonyu
 */
#include "src/display/display.h"
#include "src/logger/logger.h"

using kano_pixel_kit::Display;
using kano_pixel_kit::Logger;

std::shared_ptr<Display> display_;
std::shared_ptr<Logger> logger_;

void setup()
{
    display_ = std::make_shared<Display>();
    logger_ = std::make_shared<Logger>(&Serial);

    logger_->initialize();
    display_->initialize(logger_);

    // std::vector<Eigen::Vector3i> frame;

    // for (int i = 0; i < static_cast<int>(NeoPixel::size); i ++)
    // {
    //     Eigen::Vector3i pixel(10, 10, 10);
    // }
}

void loop()
{
}
