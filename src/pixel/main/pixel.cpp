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

#include "application/brightness.h"
#include "application/launchpad.h"
#include "application/point.h"
#include "application/restart.h"
#include "button/button.h"
#include "common/global.h"
#include "common/platform.h"
#include "display/display.h"
#include "utility/barrier.h"
#include "utility/logger.h"
#include "utility/task.h"

using namespace pixel;

void
setup()
{
    barrier_task_ = std::make_shared<Barrier>(Platform::cpu_cores);
    button_ = std::make_shared<Button>();
    display_ = std::make_shared<Display>();
    launchpad_ = std::make_shared<LaunchPad>();
    logger_ = std::make_shared<Logger>();

    auto brightness = std::make_shared<Brightness>();
    auto point = std::make_shared<Point>();
    auto restart = std::make_shared<Restart>();

    launchpad_->addApplication(point);
    launchpad_->addApplication(brightness);
    launchpad_->addService(restart);

    xTaskCreatePinnedToCore(taskCore0, task_names_[0].c_str(), 2048, NULL, 3, NULL, 0);
    xTaskCreatePinnedToCore(taskCore1, task_names_[1].c_str(), 2048, NULL, 3, NULL, 1);
}

void
loop()
{
    vTaskDelay(10);
}
