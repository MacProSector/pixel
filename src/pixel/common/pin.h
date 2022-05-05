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
 * pin.h
 *
 *  Created on: May 4, 2022
 *      Author: simonyu
 */

#ifndef COMMON_PIN_H_
#define COMMON_PIN_H_

namespace kano_pixel_kit
{
enum Pin
{
    neo_pixel = 4,
    pushbutton_right = 18,
    pushbutton_left = 23,
    joystick_right = 25,
    joystick_left = 26,
    joystick_click = 27,
    joystick_down = 34,
    joystick_up = 35,
    dial = 36
};
}   // namespace kano_pixel_kit

#endif /* COMMON_PIN_H_ */
