/*
 * buttons_test.cpp
 *
 *  Created on: Nov 20, 2021
 *      Author: simonyu
 */
#include <Arduino.h>
#include <cmath>

#include "../applications/buttons_test.h"
#include "../devices/esp32.h"
#include "../devices/neopixel.h"
#include "../display/display.h"
#include "../logger/logger.h"

namespace kano_pixel_kit
{
ButtonsTest::ButtonsTest() :
        color_dial_(Eigen::Vector3i(10, 10, 10)), color_buttons_(Eigen::Vector3i(
        10, 0, 0)), pixel_index_dial_(0), pixel_index_buttons_(0), timer_started_(
        false), timer_start_(0), timer_end_(0)
{
    frame_ = std::make_shared<std::vector<Eigen::Vector3i>>();

    for (int i = 0; i < static_cast<int>(NeoPixel::size); i ++)
    {
        frame_->push_back(Eigen::Vector3i(0, 0, 0));
    }
}

void
ButtonsTest::initialize(std::shared_ptr<Buttons> buttons, std::shared_ptr<Display> display, 
    std::shared_ptr<Logger> logger)
{
    buttons_ = buttons;
    display_ = display;
    logger_ = logger;

    states_ = buttons_->getStates();
    pixel_index_dial_ = states_->dial / static_cast<float>(
            ESP32Platform::analog_max) * (static_cast<int>(NeoPixel::size) - 1);
    frame_->at(pixel_index_dial_) = color_dial_;
    frame_->at(pixel_index_buttons_) = color_buttons_;

    display_->setFrame(*frame_);
}

void
ButtonsTest::execute()
{
    states_ = buttons_->getStates();

    if (pixel_index_dial_ != pixel_index_buttons_)
    {
        frame_->at(pixel_index_dial_) = Eigen::Vector3i(0, 0, 0);
        pixel_index_dial_ = states_->dial / static_cast<float>(
                ESP32Platform::analog_max) * (static_cast<int>(NeoPixel::size) - 1);

        if (pixel_index_dial_ != pixel_index_buttons_)
        {
            frame_->at(pixel_index_dial_) = color_dial_;
        }

        display_->setFrame(*frame_);
    }
    else
    {
        pixel_index_dial_ = states_->dial / static_cast<float>(
                ESP32Platform::analog_max) * (static_cast<int>(NeoPixel::size) - 1);
    }

    if (states_->joystick_up && pixel_index_buttons_ >= static_cast<int>(NeoPixel::width))
    {
        frame_->at(pixel_index_buttons_) = Eigen::Vector3i(0, 0, 0);
        pixel_index_buttons_ -= static_cast<int>(NeoPixel::width);
        frame_->at(pixel_index_buttons_) = color_buttons_;
        display_->setFrame(*frame_);
    }

    if (states_->joystick_down && pixel_index_buttons_ < static_cast<int>(
            NeoPixel::size) - static_cast<int>(NeoPixel::width))
    {
        frame_->at(pixel_index_buttons_) = Eigen::Vector3i(0, 0, 0);
        pixel_index_buttons_ += static_cast<int>(NeoPixel::width);
        frame_->at(pixel_index_buttons_) = color_buttons_;
        display_->setFrame(*frame_);
    }

    if ((states_->joystick_left || states_->pushbutton_left) && pixel_index_buttons_ > 0)
    {
        frame_->at(pixel_index_buttons_) = Eigen::Vector3i(0, 0, 0);
        frame_->at(--pixel_index_buttons_) = color_buttons_;
        display_->setFrame(*frame_);
    }

    if ((states_->joystick_right || states_->pushbutton_right) && pixel_index_buttons_ < static_cast<int>(
            NeoPixel::size) - 1)
    {
        frame_->at(pixel_index_buttons_) = Eigen::Vector3i(0, 0, 0);
        frame_->at(++pixel_index_buttons_) = color_buttons_;
        display_->setFrame(*frame_);
    }

    if (states_->joystick_click)
    {
        frame_->at(pixel_index_buttons_) = Eigen::Vector3i(0, 0, 0);
        pixel_index_buttons_ = 0;
        frame_->at(pixel_index_buttons_) = color_buttons_;
        display_->setFrame(*frame_);
    }

    if (states_->pushbutton_left && states_->pushbutton_right)
    {
        if (!timer_started_)
        {
            timer_start_ = millis();
            timer_started_ = true;
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
        logger_->logInfo("Restart combination triggered");
        ESP.restart();
    }
}
} // namespace kano_pixel_kit