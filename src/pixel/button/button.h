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
class Logger;

class Button
{
public:

    struct State
    {
        int dial;
        bool joystick_up;
        bool joystick_down;
        bool joystick_left;
        bool joystick_right;
        bool joystick_click;
        bool pushbutton_left;
        bool pushbutton_right;

        inline
        State() : dial(0), joystick_up(false), joystick_down(false), joystick_left(false),
                joystick_right(false), joystick_click(false), pushbutton_left(false),
                pushbutton_right(false)
        {
        }
    };

    Button();

    void
    initialize(std::shared_ptr<Logger> logger);

    std::shared_ptr<State>
    getState();

    static void
    setDial();

    static void
    setJoystickUp();

    static void
    setJoystickDown();

    static void
    setJoystickLeft();

    static void
    setJoystickRight();

    static void
    setJoystickClick();

    static void
    setPushbuttonLeft();

    static void
    setPushbuttonRight();

    static std::shared_ptr<State> state_;

private:

    std::shared_ptr<Logger> logger_;
};
}   // namespace pixel

#endif  // BUTTON_BUTTON_H_
