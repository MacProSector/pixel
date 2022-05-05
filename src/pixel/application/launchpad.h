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
 * launchpad.h
 *
 *  Created on: Nov 30, 2021
 *      Author: simonyu
 */

#ifndef SRC_KANO_PIXEL_KIT_APPLICATIONS_LAUNCHPAD_H_
#define SRC_KANO_PIXEL_KIT_APPLICATIONS_LAUNCHPAD_H_

#include "application/application.h"

namespace pixel
{
class LaunchPad : public Application
{
public:

    LaunchPad(std::shared_ptr<Button> button, std::shared_ptr<Display> display,
            std::shared_ptr<Logger> logger);

    void
    addApplication(std::shared_ptr<Application> application);

    void
    addService(std::shared_ptr<Application> service);

    void
    initialize() override;

    void
    run() override;

private:

    void
    processJoystick();

    void
    processPushbutton();

    std::shared_ptr<Application> application_;

    std::vector<std::shared_ptr<Application>> applications_;
    std::vector<std::shared_ptr<Application>> services_;

    int application_index_;
    bool application_initialized_;
    bool application_launched_;
    bool timer_started_;
    unsigned long timer_start_;
    unsigned long timer_end_;
};
}   // namespace pixel

#endif /* SRC_KANO_PIXEL_KIT_APPLICATIONS_LAUNCHPAD_H_ */
