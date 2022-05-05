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
 * interrupt.cpp
 *
 *  Created on: May 4, 2022
 *      Author: simonyu
 */

#include "common/global.h"

namespace pixel
{
void
joystickUpInterruptHandler()
{
    button_->onJoystickUpChange();
}

void
joystickDownInterruptHandler()
{
    button_->onJoystickDownChange();
}

void
joystickLeftInterruptHandler()
{
    button_->onJoystickLeftChange();
}

void
joystickRightInterruptHandler()
{
    button_->onJoystickRightChange();
}

void
joystickClickInterruptHandler()
{
    button_->onJoystickClickChange();
}

void
pushbuttonLeftInterruptHandler()
{
    button_->onPushbuttonLeftChange();
}

void
pushbuttonRightInterruptHandler()
{
    button_->onPushbuttonRightChange();
}
}   // namespace pixel
