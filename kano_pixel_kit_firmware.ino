/*
 * kano_pixel_kit.ino
 *
 *  Created on: Nov 19, 2021
 *      Author: simonyu
 */
#include "src/devices/neopixel.h"
#include "src/display/display.h"
#include "src/logger/logger.h"

using kano_pixel_kit::Display;
using kano_pixel_kit::Logger;
using kano_pixel_kit::NeoPixel;

std::shared_ptr<Display> display_;
std::shared_ptr<Logger> logger_;

const std::string task_name_core_0("Core 0");
const std::string task_name_core_1("Core 1");

void
taskCore0(void *pvParameters)
{
    logger_->logInfo("Started task \"" + task_name_core_0 + "\" on core " + std::to_string(xPortGetCoreID()));

    auto frame = std::make_shared<std::vector<Eigen::Vector3i>>();

    for (int i = 0; i < static_cast<int>(NeoPixel::size); i ++)
    {
        frame->push_back(Eigen::Vector3i(10, 10, 10));
    }

    display_->setFrame(*frame);

    for(;;)
    {
        vTaskDelay(10);
    }
}

void
taskCore1(void *pvParameters)
{
    logger_->logInfo("Started task \"" + task_name_core_1 + "\" on core " + std::to_string(xPortGetCoreID()));

    for(;;)
    {
        vTaskDelay(10);
    }
}

void
setup()
{
    display_ = std::make_shared<Display>();
    logger_ = std::make_shared<Logger>(&Serial);

    logger_->initialize();
    display_->initialize(logger_);

    xTaskCreatePinnedToCore(taskCore0, task_name_core_0.c_str(), 2048, NULL, 3, NULL, 0);
    xTaskCreatePinnedToCore(taskCore1, task_name_core_1.c_str(), 2048, NULL, 3, NULL, 1);
}

void
loop()
{
    vTaskDelay(10);
}
