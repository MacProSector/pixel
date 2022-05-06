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
 * barrier.h
 *
 *  Created on: May 5, 2022
 *      Author: simonyu
 */

#ifndef UTILITY_BARRIER_H_
#define UTILITY_BARRIER_H_

#include <mutex>

namespace pixel
{
class Barrier
{
public:

    Barrier(const std::size_t& count);

    void
    arrive();

    void
    wait();

    void
    arriveAndWait();

private:

    volatile std::size_t count_;

    std::mutex mutex_;
    std::unique_lock<std::mutex> lock_;
};
}   // namespace pixel

#endif  // UTILITY_BARRIER_H_
