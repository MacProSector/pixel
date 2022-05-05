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
 * interrupt.h
 *
 *  Created on: May 4, 2022
 *      Author: simonyu
 */

#ifndef UTILITY_INTERRUPT_H_
#define UTILITY_INTERRUPT_H_

namespace pixel
{
void
joystickUpInterruptHandler();

void
joystickDownInterruptHandler();

void
joystickLeftInterruptHandler();

void
joystickRightInterruptHandler();

void
joystickClickInterruptHandler();

void
pushbuttonLeftInterruptHandler();

void
pushbuttonRightInterruptHandler();
}   // namespace pixel

#endif  // UTILITY_INTERRUPT_H_
