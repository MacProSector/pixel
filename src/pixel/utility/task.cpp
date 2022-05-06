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
 * task.cpp
 *
 *  Created on: May 6, 2022
 *      Author: simonyu
 */

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "application/launchpad.h"
#include "button/button.h"
#include "common/global.h"
#include "display/display.h"
#include "utility/barrier.h"
#include "utility/logger.h"
#include "utility/task.h"

namespace pixel
{
void
taskCore0(void* pvParameters)
{
    barrier_task_->arriveAndWait();

    launchpad_->initialize();

    logTaskStart();

    for (;;)
    {
        launchpad_->run();
        vTaskDelay(10);
    }
}

void
taskCore1(void* pvParameters)
{
    button_->initialize();
    display_->initialize();

    barrier_task_->arriveAndWait();

    logTaskStart();

    for (;;)
    {
        button_->update();
        vTaskDelay(10);
    }
}

void
logTaskStart()
{
    const auto core_index = xPortGetCoreID();

    logger_->logInfo(
            "Started task \"" + task_names_[core_index] + "\" on core "
                    + std::to_string(core_index));
}
}   // namespace pixel
