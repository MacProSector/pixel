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

void
taskCore0(void *pvParameters)
{
    logger_->logInfo("Started core 0 task");

    std::vector<Eigen::Vector3i> frame;

    for (int i = 0; i < static_cast<int>(NeoPixel::size); i ++)
    {
        frame.push_back(Eigen::Vector3i(10, 10, 10));
    }

    display_->setFrame(frame);

    for(;;)
    {
        vTaskDelay(10);
    }
}

void
taskCore1(void *pvParameters)
{
    logger_->logInfo("Started core 1 task");

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

    xTaskCreatePinnedToCore(taskCore0, "Core 0 Task", 1024, NULL, 3, NULL, 0);
    xTaskCreatePinnedToCore(taskCore1, "Core 1 Task", 1024, NULL, 3, NULL, 1);
}

void
loop()
{
    vTaskDelay(10);
}
