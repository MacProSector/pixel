/*
 * kano_pixel_kit.ino
 *
 *  Created on: Nov 19, 2021
 *      Author: simonyu
 */
#include "src/buttons/buttons.h"
#include "src/display/display.h"
#include "src/devices/esp32.h"
#include "src/applications/launchpad.h"
#include "src/logger/logger.h"
#include "src/applications/point.h"
#include "src/applications/restart.h"

using kano_pixel_kit::Buttons;
using kano_pixel_kit::Display;
using kano_pixel_kit::ESP32Platform;
using kano_pixel_kit::LaunchPad;
using kano_pixel_kit::Logger;
using kano_pixel_kit::Point;
using kano_pixel_kit::Restart;

std::shared_ptr<Buttons> buttons_;
std::shared_ptr<Display> display_;
std::shared_ptr<LaunchPad> launchpad_;
std::shared_ptr<Logger> logger_;
std::shared_ptr<Point> point_;
std::shared_ptr<Restart> restart_;
std::shared_ptr<Buttons::States> Buttons::states_;

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
    };

    const int task_core_index = xPortGetCoreID();
    const auto task_name_core = task_names_core_[task_core_index];
    const std::string task_core = std::to_string(task_core_index);

    logger_->logInfo("Started task \"" + task_name_core + "\" on core " + task_core);
}

// Applications, services, etc.
void
taskCore0(void *pvParameters)
{
    waitOnBarrier();

    launchpad_->initialize();

    for(;;)
    {
        launchpad_->run();
        vTaskDelay(10);
    }
}

// Events, interrupts, etc.
void
taskCore1(void *pvParameters)
{
    buttons_->initialize(logger_);
    display_->initialize(logger_, 10);

    waitOnBarrier();

    for(;;)
    {
        buttons_->setDial();
        vTaskDelay(10);
    }
}

void
setup()
{
    buttons_ = std::make_shared<Buttons>();
    display_ = std::make_shared<Display>();
    logger_ = std::make_shared<Logger>();
    Buttons::states_ = std::make_shared<Buttons::States>();

    logger_->initialize();

    launchpad_ = std::make_shared<LaunchPad>(buttons_, display_, logger_);
    point_ = std::make_shared<Point>(buttons_, display_, logger_);
    restart_ = std::make_shared<Restart>(buttons_, display_, logger_);

    launchpad_->addApplication(point_);
    launchpad_->addService(restart_);

    task_barrier_ = static_cast<int>(ESP32Platform::cpu_cores);
    task_names_core_ = {"Core 0",  "Core 1"};

    xTaskCreatePinnedToCore(taskCore0, task_names_core_[0].c_str(), 2048, NULL, 3, NULL, 0);
    xTaskCreatePinnedToCore(taskCore1, task_names_core_[1].c_str(), 2048, NULL, 3, NULL, 1);
}

void
loop()
{
    vTaskDelay(10);
}