/*
 * kano_pixel_kit.ino
 *
 *  Created on: Nov 19, 2021
 *      Author: simonyu
 */
#include <cmath>

#include "src/buttons/buttons.h"
#include "src/devices/esp32.h"
#include "src/devices/neopixel.h"
#include "src/display/display.h"
#include "src/logger/logger.h"

using kano_pixel_kit::Buttons;
using kano_pixel_kit::Display;
using kano_pixel_kit::ESP32Platform;
using kano_pixel_kit::Logger;
using kano_pixel_kit::NeoPixel;

std::shared_ptr<Buttons> buttons_;
std::shared_ptr<Display> display_;
std::shared_ptr<Logger> logger_;
std::shared_ptr<Buttons::States> Buttons::states_ = std::make_shared<Buttons::States>();

const std::vector<std::string> task_names_core_ = {"Core 0",  "Core 1"};
volatile int task_barrier_ = static_cast<int>(ESP32Platform::cpu_cores);
std::mutex task_barrier_mutex_;

void
waitOnBarrier()
{
    std::unique_lock<std::mutex> lock(task_barrier_mutex_);
    task_barrier_ --;
    lock.unlock();

    while (task_barrier_)
    {
        vTaskDelay(10);
    };

    const int task_core_index = xPortGetCoreID();
    const auto task_name_core = task_names_core_[task_core_index];
    const std::string task_core = std::to_string(task_core_index);

    logger_->logInfo("Started task \"" + task_name_core + "\" on core " + task_core);
}

void
taskCore0(void *pvParameters)
{
    buttons_->initialize(logger_);

    waitOnBarrier();

    for(;;)
    {
        buttons_->setDial();
        vTaskDelay(10);
    }
}

void
taskCore1(void *pvParameters)
{
    display_->initialize(logger_);

    auto frame = std::make_shared<std::vector<Eigen::Vector3i>>();
    Eigen::Vector3i color_dial = Eigen::Vector3i(10, 10, 10);
    Eigen::Vector3i color_buttons = Eigen::Vector3i(10, 0, 0);
    volatile int pixel_index_dial = buttons_->states_->dial / static_cast<float>(ESP32Platform::analog_max) * (static_cast<int>(NeoPixel::size) - 1);
    volatile int pixel_index_buttons = 0;
    volatile bool timer_started = false;
    volatile unsigned long timer_start = 0;
    volatile unsigned long timer_end = 0;

    for (int i = 0; i < static_cast<int>(NeoPixel::size); i ++)
    {
        frame->push_back(Eigen::Vector3i(0, 0, 0));
    }

    frame->at(pixel_index_dial) = color_dial;
    frame->at(pixel_index_buttons) = color_buttons;
    display_->setFrame(*frame);

    waitOnBarrier();

    for(;;)
    {
        auto states = buttons_->getStates();

        if (pixel_index_dial != pixel_index_buttons)
        {
            frame->at(pixel_index_dial) = Eigen::Vector3i(0, 0, 0);
            pixel_index_dial = states->dial / static_cast<float>(ESP32Platform::analog_max) * (static_cast<int>(NeoPixel::size) - 1);

            if (pixel_index_dial != pixel_index_buttons)
            {
                frame->at(pixel_index_dial) = color_dial;
            }

            display_->setFrame(*frame);
        }
        else
        {
            pixel_index_dial = states->dial / static_cast<float>(ESP32Platform::analog_max) * (static_cast<int>(NeoPixel::size) - 1);
        }

        if (states->joystick_up && pixel_index_buttons >= static_cast<int>(NeoPixel::width))
        {
            frame->at(pixel_index_buttons) = Eigen::Vector3i(0, 0, 0);
            pixel_index_buttons -= static_cast<int>(NeoPixel::width);
            frame->at(pixel_index_buttons) = color_buttons;
            display_->setFrame(*frame);
        }

        if (states->joystick_down && pixel_index_buttons < static_cast<int>(NeoPixel::size) - static_cast<int>(NeoPixel::width))
        {
            frame->at(pixel_index_buttons) = Eigen::Vector3i(0, 0, 0);
            pixel_index_buttons += static_cast<int>(NeoPixel::width);
            frame->at(pixel_index_buttons) = color_buttons;
            display_->setFrame(*frame);
        }

        if ((states->joystick_left || states->pushbutton_left) && pixel_index_buttons > 0)
        {
            frame->at(pixel_index_buttons) = Eigen::Vector3i(0, 0, 0);
            frame->at(--pixel_index_buttons) = color_buttons;
            display_->setFrame(*frame);
        }

        if ((states->joystick_right || states->pushbutton_right) && pixel_index_buttons < static_cast<int>(NeoPixel::size) - 1)
        {
            frame->at(pixel_index_buttons) = Eigen::Vector3i(0, 0, 0);
            frame->at(++pixel_index_buttons) = color_buttons;
            display_->setFrame(*frame);
        }

        if (states->joystick_click)
        {
            frame->at(pixel_index_buttons) = Eigen::Vector3i(0, 0, 0);
            pixel_index_buttons = 0;
            frame->at(pixel_index_buttons) = color_buttons;
            display_->setFrame(*frame);
        }

        if (states->pushbutton_left && states->pushbutton_right)
        {
            if (!timer_started)
            {
                timer_start = millis();
                timer_started = true;
            }

            timer_end = millis();
        }
        else
        {
            timer_started = false;
            timer_start = millis();
            timer_end = timer_start;
        }

        if (timer_end - timer_start > 5000)
        {
            logger_->logInfo("Restart combination triggered");
            ESP.restart();
        }

        vTaskDelay(10);
    }
}

void
setup()
{
    buttons_ = std::make_shared<Buttons>();
    display_ = std::make_shared<Display>();
    logger_ = std::make_shared<Logger>(&Serial);

    logger_->initialize();

    xTaskCreatePinnedToCore(taskCore0, task_names_core_[0].c_str(), 2048, NULL, 3, NULL, 0);
    xTaskCreatePinnedToCore(taskCore1, task_names_core_[1].c_str(), 2048, NULL, 3, NULL, 1);
}

void
loop()
{
    vTaskDelay(10);
}
