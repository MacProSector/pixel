/*
 * launchpad.cpp
 *
 *  Created on: Nov 20, 2021
 *      Author: simonyu
 */
#include "application/launchpad.h"

namespace kano_pixel_kit
{
LaunchPad::LaunchPad(std::shared_ptr<Button> button, std::shared_ptr<Display> display,
        std::shared_ptr<Logger> logger) : Application(button, display, logger),
        application_index_(0), application_initialized_(false), application_launched_(false),
        timer_started_(false), timer_start_(0), timer_end_(0)
{
}

void
LaunchPad::addApplication(std::shared_ptr<Application> application)
{
    applications_.push_back(application);
}

void
LaunchPad::addService(std::shared_ptr<Application> service)
{
    services_.push_back(service);
}

void
LaunchPad::initialize()
{
    for (auto service : services_)
    {
        service->initialize();
    }
}

void
LaunchPad::run()
{
    button_state_ = button_->getState();

    processJoystick();
    processPushbutton();

    if (application_launched_)
    {
        if (!application_initialized_)
        {
            application_->initialize();
            application_initialized_ = true;
        }

        application_->run();
    }
    else
    {
        application_initialized_ = false;
        display_->setFrameAtomic(applications_[application_index_]->getSplashScreen());
    }

    for (auto service : services_)
    {
        service->run();
    }
}

void
LaunchPad::processJoystick()
{
    static bool joystick_click_reset = false;
    static bool joystick_click_last = true; // Require reset after restart

    if (!application_launched_)
    {
        static bool joystick_left_last = false;
        static bool joystick_right_last = false;

        if (joystick_left_last && !button_state_->joystick_left && application_index_ > 0)
        {
            application_index_ --;
        }

        if (joystick_right_last && !button_state_->joystick_right
                && application_index_ < applications_.size() - 1)
        {
            application_index_ ++;
        }

        if (!joystick_click_last && button_state_->joystick_click)
        {
            joystick_click_reset = true;
        }

        if (!application_launched_ && joystick_click_reset && joystick_click_last
                && !button_state_->joystick_click)
        {
            application_ = applications_[application_index_];
            application_launched_ = true;
        }

        joystick_left_last = button_state_->joystick_left;
        joystick_right_last = button_state_->joystick_right;
    }
    else
    {
        if (button_state_->joystick_click)
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

        if (timer_end_ - timer_start_ > 1000)
        {
            application_launched_ = false;
            joystick_click_reset = false;
        }
    }

    joystick_click_last = button_state_->joystick_click;
}

void
LaunchPad::processPushbutton()
{
    if (application_launched_)
    {
        return;
    }

    static bool pushbutton_left_last = false;
    static bool pushbutton_right_last = false;

    if (pushbutton_left_last && !button_state_->pushbutton_left && application_index_ > 0)
    {
        application_index_ --;
    }

    if (pushbutton_right_last && !button_state_->pushbutton_right
            && application_index_ < applications_.size() - 1)
    {
        application_index_ ++;
    }

    pushbutton_left_last = button_state_->pushbutton_left;
    pushbutton_right_last = button_state_->pushbutton_right;
}
} // namespace kano_pixel_kit
