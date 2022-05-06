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
 * restart.h
 *
 *  Created on: Nov 20, 2021
 *      Author: simonyu
 */

#ifndef APPLICATION_RESTART_H_
#define APPLICATION_RESTART_H_

#include "application/application.h"

namespace pixel
{
class Restart : public Application
{
public:

    Restart();

    void
    initialize() override;

    void
    run() override;

private:

    void
    displayRestartScreen();

    bool timer_started_;
    unsigned long timer_start_;
    unsigned long timer_end_;
};
}   // namespace pixel

#endif  // APPLICATION_RESTART_H_
