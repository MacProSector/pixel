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
 * button.h
 *
 *  Created on: Nov 20, 2021
 *      Author: simonyu
 */

#ifndef BUTTON_BUTTON_H_
#define BUTTON_BUTTON_H_

#include <memory>

namespace pixel
{
class ButtonState;

class Button
{
public:

    Button();

    void
    initialize();

    std::shared_ptr<ButtonState>
    getButtonState();

    void
    onJoystickUpChange();

    void
    onJoystickDownChange();

    void
    onJoystickLeftChange();

    void
    onJoystickRightChange();

    void
    onJoystickClickChange();

    void
    onPushbuttonLeftChange();

    void
    onPushbuttonRightChange();

    void
    update();

private:

    void
    readDial();

    std::shared_ptr<ButtonState> button_state_;
};
}   // namespace pixel

#endif  // BUTTON_BUTTON_H_
