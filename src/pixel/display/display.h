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
 * display.h
 *
 *  Created on: Nov 19, 2021
 *      Author: simonyu
 */

#ifndef DISPLAY_DISPLAY_H_
#define DISPLAY_DISPLAY_H_

#include <Adafruit_NeoPixel.h>
#include <ArduinoEigenDense.h>
#include <memory>
#include <mutex>
#include <vector>

namespace pixel
{
class Display
{
public:

    Display();

    void
    initialize();

    bool
    lock();

    void
    unlock();

    void
    setBrightness(const int& brightness);

    void
    setFrame(std::shared_ptr<std::vector<Eigen::Vector3i>> frame);

    bool
    setFrameAtomic(std::shared_ptr<std::vector<Eigen::Vector3i>> frame);

    void
    clear();

private:

    void
    displayStartScreen();

    Adafruit_NeoPixel neopixel_;

    std::shared_ptr<std::vector<Eigen::Vector3i>> frame_;

    std::mutex mutex_;
    std::unique_lock<std::mutex> lock_;
};
}   // namespace pixel

#endif  // DISPLAY_DISPLAY_H_
