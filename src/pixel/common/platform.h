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
 * platform.h
 *
 *  Created on: Nov 19, 2021
 *      Author: simonyu
 */

#ifndef SRC_KANO_PIXEL_KIT_DEVICES_ESP32_H_
#define SRC_KANO_PIXEL_KIT_DEVICES_ESP32_H_

namespace kano_pixel_kit
{
enum Platform
{
    cpu_cores = 2,
    analog_max = 4095
};

enum PlatformNeoPixel
{
    height = 8,
    width = 16,
    size = 128,
    value_max = 255,
    brightness_min = 10,
    brightness_max = 30
};

enum PlatformSerial
{
    baud_rate = 115200
};
} // namespace kano_pixel_kit

#endif /* SRC_KANO_PIXEL_KIT_DEVICES_ESP32_H_ */
