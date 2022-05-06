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
 * global.cpp
 *
 *  Created on: May 5, 2022
 *      Author: simonyu
 */

#include "application/launchpad.h"
#include "common/global.h"
#include "display/display.h"
#include "button/button.h"
#include "utility/barrier.h"
#include "utility/logger.h"

namespace pixel
{
std::shared_ptr<Barrier> barrier_task_;
std::shared_ptr<Button> button_;
std::shared_ptr<Display> display_;
std::shared_ptr<LaunchPad> launchpad_;
std::shared_ptr<Logger> logger_;

std::vector<std::string> task_names_ = {"Core 0", "Core 1"};
}   // namespace pixel
