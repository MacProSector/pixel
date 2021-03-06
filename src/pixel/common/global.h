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
 * global.h
 *
 *  Created on: May 5, 2022
 *      Author: simonyu
 */

#ifndef COMMON_GLOBAL_H_
#define COMMON_GLOBAL_H_

#include <memory>
#include <string>
#include <vector>

namespace pixel
{
class Barrier;
class Button;
class Display;
class LaunchPad;
class Logger;

extern std::shared_ptr<Barrier> barrier_task_;
extern std::shared_ptr<Button> button_;
extern std::shared_ptr<Display> display_;
extern std::shared_ptr<LaunchPad> launchpad_;
extern std::shared_ptr<Logger> logger_;

extern std::vector<std::string> task_names_;
}   // namespace pixel

#endif /* COMMON_GLOBAL_H_ */
