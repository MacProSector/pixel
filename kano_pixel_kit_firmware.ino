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

volatile int task_barrier_ = static_cast<int>(ESP32Platform::cpu_cores);
std::mutex task_barrier_mutex_;
const std::string task_name_core_0_("Core 0");
const std::string task_name_core_1_("Core 1");

void
taskCore0(void *pvParameters)
{
    buttons_->initialize(logger_);

    std::unique_lock<std::mutex> lock(task_barrier_mutex_);
    task_barrier_ --;
    lock.unlock();

    while (task_barrier_)
    {
        vTaskDelay(10);
    };

    logger_->logInfo("Started task \"" + task_name_core_0_ + "\" on core " + std::to_string(xPortGetCoreID()));

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
    Eigen::Vector3i color_pushbutton = Eigen::Vector3i(10, 0, 0);
    Eigen::Vector3i color_dial = Eigen::Vector3i(10, 10, 10);
    volatile int pixel_index_pushbutton = 0;
    volatile int pixel_index_dial = buttons_->states_->dial / static_cast<float>(ESP32Platform::analog_max) * (static_cast<int>(NeoPixel::size) - 1);

    for (int i = 0; i < static_cast<int>(NeoPixel::size); i ++)
    {
        frame->push_back(Eigen::Vector3i(0, 0, 0));
    }

    frame->at(pixel_index_dial) = color_dial;
    frame->at(pixel_index_pushbutton) = color_pushbutton;
    display_->setFrame(*frame);

    std::unique_lock<std::mutex> lock(task_barrier_mutex_);
    task_barrier_ --;
    lock.unlock();

    while (task_barrier_)
    {
        vTaskDelay(10);
    };

    logger_->logInfo("Started task \"" + task_name_core_1_ + "\" on core " + std::to_string(xPortGetCoreID()));

    for(;;)
    {
        volatile bool pushbutton_left = buttons_->states_->pushbutton_left;
        volatile bool pushbutton_right = buttons_->states_->pushbutton_right;
        volatile int dial = buttons_->states_->dial;

        if (pushbutton_left && pixel_index_pushbutton > 0)
        {
            frame->at(pixel_index_pushbutton) = Eigen::Vector3i(0, 0, 0);
            frame->at(--pixel_index_pushbutton) = color_pushbutton;
            display_->setFrame(*frame);
        }

        if (pushbutton_right && pixel_index_pushbutton < static_cast<int>(NeoPixel::size) - 1)
        {
            frame->at(pixel_index_pushbutton) = Eigen::Vector3i(0, 0, 0);
            frame->at(++pixel_index_pushbutton) = color_pushbutton;
            display_->setFrame(*frame);
        }

        if (pixel_index_dial != pixel_index_pushbutton)
        {
            frame->at(pixel_index_dial) = Eigen::Vector3i(0, 0, 0);
            pixel_index_dial = dial / static_cast<float>(ESP32Platform::analog_max) * (static_cast<int>(NeoPixel::size) - 1);

            if (pixel_index_dial != pixel_index_pushbutton)
            {
                frame->at(pixel_index_dial) = color_dial;
            }

            display_->setFrame(*frame);
        }
        else
        {
            pixel_index_dial = dial / static_cast<float>(ESP32Platform::analog_max) * (static_cast<int>(NeoPixel::size) - 1);
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

    xTaskCreatePinnedToCore(taskCore0, task_name_core_0_.c_str(), 2048, NULL, 3, NULL, 0);
    xTaskCreatePinnedToCore(taskCore1, task_name_core_1_.c_str(), 2048, NULL, 3, NULL, 1);
}

void
loop()
{
    vTaskDelay(10);
}
