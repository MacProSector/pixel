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
 * application.h
 *
 *  Created on: Nov 30, 2021
 *      Author: simonyu
 */

#ifndef APPLICATION_APPLICATION_H_
#define APPLICATION_APPLICATION_H_

#include <ArduinoEigenDense.h>
#include <memory>
#include <vector>

namespace pixel
{
class Application
{
public:

    Application();

    virtual
    ~Application() = default;

    virtual void
    initialize() = 0;

    virtual void
    run() = 0;

    std::shared_ptr<std::vector<Eigen::Vector3i>>
    getSplashScreen() const;

protected:

    std::shared_ptr<std::vector<Eigen::Vector3i>> display_frame_;
    std::shared_ptr<std::vector<Eigen::Vector3i>> display_frame_splash_;
};
}   // namespace pixel

#endif  // APPLICATION_APPLICATION_H_
