/*
 * restart.cpp
 *
 *  Created on: Nov 20, 2021
 *      Author: simonyu
 */
#include <Arduino.h>

#include "../applications/restart.h"
#include "../devices/neopixel.h"

namespace kano_pixel_kit
{
Restart::Restart(std::shared_ptr<Buttons> buttons, std::shared_ptr<Display> display,
        std::shared_ptr<Logger> logger) : Application(buttons, display, logger), timer_started_(
        false), timer_start_(0), timer_end_(0)
{
}

void
Restart::initialize()
{
    buttons_state_ = buttons_->getStates();
    display_frame_->clear();

    for (int i = 0; i < static_cast<int>(NeoPixel::size); i ++)
    {
        display_frame_->push_back(Eigen::Vector3i(255, 0, 0));
    }
}

void
Restart::run()
{
    buttons_state_ = buttons_->getStates();

    if (buttons_state_->joystick_click)
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