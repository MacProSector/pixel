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
 * barrier.cpp
 *
 *  Created on: May 5, 2022
 *      Author: simonyu
 */

#include "utility/barrier.h"

namespace pixel
{
Barrier::Barrier(const std::size_t& count) : count_(count), lock_(mutex_, std::defer_lock)
{
}

void
Barrier::arrive()
{
    lock_.lock();
    count_ --;
    lock_.unlock();
}

void
Barrier::wait()
{
    std::size_t count;

    do
    {
        lock_.lock();
        count = count_;
        lock_.unlock();
    }
    while (count);
}

void
Barrier::arriveAndWait()
{
    arrive();
    wait();
}
}   // namespace pixel
