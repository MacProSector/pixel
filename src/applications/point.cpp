/*
 * point.cpp
 *
 *  Created on: Nov 20, 2021
 *      Author: simonyu
 */
#include "../applications/point.h"
#include "../devices/esp32.h"
#include "../devices/neopixel.h"

namespace kano_pixel_kit
{
Point::Point(std::shared_ptr<Buttons> buttons, std::shared_ptr<Display> display,
        std::shared_ptr<Logger> logger) : Application(buttons, display, logger), 
        color_dial_(Eigen::Vector3i(0, 0, 255)), color_buttons_(Eigen::Vector3i(
        255, 0, 0)), pixel_index_dial_(0), pixel_index_buttons_(0), set_display_frame_(false)
{
    display_frame_splash_->at(static_cast<int>(NeoPixel::size) / 3 + 2) = (color_dial_.cast<float>() * 0.4).cast<int>();
    display_frame_splash_->at(static_cast<int>(NeoPixel::size) / 3 + 1) = (color_dial_.cast<float>() * 0.6).cast<int>();
    display_frame_splash_->at(static_cast<int>(NeoPixel::size) / 3) = (color_dial_.cast<float>() * 0.8).cast<int>();
    display_frame_splash_->at(static_cast<int>(NeoPixel::size) / 3 - 1) = color_dial_;

    display_frame_splash_->at(static_cast<int>(NeoPixel::size) / 3 * 2 - 1) = (color_buttons_.cast<float>() * 0.4).cast<int>();
    display_frame_splash_->at(static_cast<int>(NeoPixel::size) / 3 * 2) = (color_buttons_.cast<float>() * 0.6).cast<int>();
    display_frame_splash_->at(static_cast<int>(NeoPixel::size) / 3 * 2 + 1) = (color_buttons_.cast<float>() * 0.8).cast<int>();
    display_frame_splash_->at(static_cast<int>(NeoPixel::size) / 3 * 2 + 2) = color_buttons_;
}

void
Point::initialize()
{
    buttons_state_ = buttons_->getStates();
    pixel_index_dial_ = buttons_state_->dial / static_cast<float>(
            ESP32Platform::analog_max) * (static_cast<int>(NeoPixel::size) - 1);
    display_frame_->at(pixel_index_dial_) = color_dial_;
    display_frame_->at(pixel_index_buttons_) = color_buttons_;

    display_->setFrameAtomic(display_frame_);
}

void
Point::run()
{
    buttons_state_ = buttons_->getStates();
    set_display_frame_ = false;

    processDial();
    processJoystick();
    processPushbutton();

    if (set_display_frame_)
    {
        std::fill(display_frame_->begin(), display_frame_->end(), Eigen::Vector3i(0, 0, 0));

        display_frame_->at(pixel_index_dial_) = color_dial_;
        display_frame_->at(pixel_index_buttons_) = color_buttons_;

        display_->setFrameAtomic(display_frame_);
    }
}

void
Point::processDial()
{
    static int pixel_index_dial_last = 0;

    pixel_index_dial_ = buttons_state_->dial / static_cast<float>(
            ESP32Platform::analog_max) * (static_cast<int>(NeoPixel::size) - 1);

    if (pixel_index_dial_ != pixel_index_dial_last)
    {
        set_display_frame_ = true;
    }

    pixel_index_dial_last = pixel_index_dial_;
}

void
Point::processJoystick()
{
    if (buttons_state_->joystick_up && pixel_index_buttons_ >= static_cast<int>(NeoPixel::width))
    {
        pixel_index_buttons_ -= static_cast<int>(NeoPixel::width);
        set_display_frame_ = true;
    }

    if (buttons_state_->joystick_down && pixel_index_buttons_ < static_cast<int>(
            NeoPixel::size) - static_cast<int>(NeoPixel::width))
    {
        pixel_index_buttons_ += static_cast<int>(NeoPixel::width);
        set_display_frame_ = true;
    }

    if (buttons_state_->joystick_left && pixel_index_buttons_ % static_cast<int>(
            NeoPixel::width) > 0)
    {
        pixel_index_buttons_ --;
        set_display_frame_ = true;
    }

    if (buttons_state_->joystick_right && pixel_index_buttons_ % static_cast<int>(
            NeoPixel::width) < static_cast<int>(NeoPixel::width) - 1)
    {
        pixel_index_buttons_ ++;
        set_display_frame_ = true;
    }
}

void
Point::processPushbutton()
{
    if (buttons_state_->pushbutton_left && pixel_index_buttons_ > 0)
    {
        pixel_index_buttons_ --;
        set_display_frame_ = true;
    }

    if (buttons_state_->pushbutton_right && pixel_index_buttons_ < static_cast<int>(
            NeoPixel::size) - 1)
    {
        pixel_index_buttons_ ++;
        set_display_frame_ = true;
    }
}
} // namespace kano_pixel_kit