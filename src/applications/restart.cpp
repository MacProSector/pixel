/*
 * restart.cpp
 *
 *  Created on: Nov 20, 2021
 *      Author: simonyu
 */
#include <Arduino.h>

#include "../applications/restart.h"
#include "../devices/neopixel.h"
#include "../logger/logger.h"

namespace kano_pixel_kit
{
Restart::Restart() :
        timer_started_(false), timer_start_(0), timer_end_(0)
{
    frame_ = std::make_shared<std::vector<Eigen::Vector3i>>();

    for (int i = 0; i < static_cast<int>(NeoPixel::size); i ++)
    {
        frame_->push_back(Eigen::Vector3i(10, 0, 0));
    }
}

void
Restart::initialize(std::shared_ptr<Buttons> buttons, std::shared_ptr<Display> display,
        std::shared_ptr<Logger> logger)
{
    buttons_ = buttons;
    display_ = display;
    logger_ = logger;

    states_ = buttons_->getStates();
}

void
Restart::run()
{
    states_ = buttons_->getStates();

    if (states_->joystick_click)
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
        ESP.restart();
    }
}
} // namespace kano_pixel_kit