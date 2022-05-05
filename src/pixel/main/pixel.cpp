/*
 *  Copyright (C) 2022  Simon Yu
 *
 *  Developed by:   Simon Yu (yujunda@icloud.com)
 *                  https://www.simonyu.net/
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

/*
 * pixel.cpp
 *
 *  Created on: Nov 19, 2021
 *      Author: simonyu
 */

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/portmacro.h>

#include "application/brightness.h"
#include "button/button.h"
#include "display/display.h"
#include "application/launchpad.h"
#include "utility/logger.h"
#include "common/platform.h"
#include "application/point.h"
#include "application/restart.h"

using namespace kano_pixel_kit;

std::shared_ptr<Brightness> brightness_;
std::shared_ptr<Button> button_;
std::shared_ptr<Display> display_;
std::shared_ptr<LaunchPad> launchpad_;
std::shared_ptr<Logger> logger_;
std::shared_ptr<Point> point_;
std::shared_ptr<Restart> restart_;
std::shared_ptr<Button::State> Button::state_;

volatile int task_barrier_;
std::mutex task_barrier_mutex_;
std::vector<std::string> task_names_core_;

void
waitOnBarrier()
{
    std::unique_lock<std::mutex> lock(task_barrier_mutex_);
    task_barrier_ --;
    lock.unlock();

    while (task_barrier_)
    {
        vTaskDelay(10);
    }

    const int task_core_index = xPortGetCoreID();
    const auto task_name_core = task_names_core_[task_core_index];
    const std::string task_core = std::to_string(task_core_index);

    logger_->logInfo("Started task \"" + task_name_core + "\" on core " + task_core);
}

// Applications, services, etc.
void
taskCore0(void* pvParameters)
{
    waitOnBarrier();

    launchpad_->initialize();

    for (;;)
    {
        launchpad_->run();
        vTaskDelay(10);
    }
}

// Events, interrupts, etc.
void
taskCore1(void* pvParameters)
{
    button_->initialize(logger_);
    display_->initialize(logger_);

    waitOnBarrier();

    for (;;)
    {
        button_->setDial();
        vTaskDelay(10);
    }
}

void
setup()
{
    button_ = std::make_shared<Button>();
    display_ = std::make_shared<Display>();
    logger_ = std::make_shared<Logger>();
    Button::state_ = std::make_shared<Button::State>();

    brightness_ = std::make_shared<Brightness>(button_, display_, logger_);
    launchpad_ = std::make_shared<LaunchPad>(button_, display_, logger_);
    point_ = std::make_shared<Point>(button_, display_, logger_);
    restart_ = std::make_shared<Restart>(button_, display_, logger_);

    launchpad_->addApplication(point_);
    launchpad_->addApplication(brightness_);
    launchpad_->addService(restart_);

    task_barrier_ = Platform::cpu_cores;
    task_names_core_ = {"Core 0", "Core 1"};

    xTaskCreatePinnedToCore(taskCore0, task_names_core_[0].c_str(), 2048, NULL, 3, NULL, 0);
    xTaskCreatePinnedToCore(taskCore1, task_names_core_[1].c_str(), 2048, NULL, 3, NULL, 1);
}

void
loop()
{
    vTaskDelay(10);
}
