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
 * button.cpp
 *
 *  Created on: Nov 20, 2021
 *      Author: simonyu
 */

#include <Arduino.h>

#include "button/button.h"
#include "utility/logger.h"
#include "common/pin.h"

namespace pixel
{
Button::Button()
{
}

void
Button::initialize(std::shared_ptr<Logger> logger)
{
    logger_ = logger;

    pinMode(digitalPinToInterrupt(Pin::dial), INPUT);
    pinMode(digitalPinToInterrupt(Pin::joystick_up), INPUT);
    pinMode(digitalPinToInterrupt(Pin::joystick_down), INPUT);
    pinMode(digitalPinToInterrupt(Pin::joystick_left), INPUT);
    pinMode(digitalPinToInterrupt(Pin::joystick_right), INPUT);
    pinMode(digitalPinToInterrupt(Pin::joystick_click), INPUT);
    pinMode(digitalPinToInterrupt(Pin::pushbutton_left), INPUT);
    pinMode(digitalPinToInterrupt(Pin::pushbutton_right), INPUT);

    setDial();
    setJoystickUp();
    setJoystickDown();
    setJoystickLeft();
    setJoystickRight();
    setJoystickClick();
    setPushbuttonLeft();
    setPushbuttonRight();

    attachInterrupt(digitalPinToInterrupt(Pin::joystick_up), Button::setJoystickUp, CHANGE);
    attachInterrupt(digitalPinToInterrupt(Pin::joystick_down), Button::setJoystickDown, CHANGE);
    attachInterrupt(digitalPinToInterrupt(Pin::joystick_left), Button::setJoystickLeft, CHANGE);
    attachInterrupt(digitalPinToInterrupt(Pin::joystick_right), Button::setJoystickRight, CHANGE);
    attachInterrupt(digitalPinToInterrupt(Pin::joystick_click), Button::setJoystickClick, CHANGE);
    attachInterrupt(digitalPinToInterrupt(Pin::pushbutton_left), Button::setPushbuttonLeft, CHANGE);
    attachInterrupt(digitalPinToInterrupt(Pin::pushbutton_right), Button::setPushbuttonRight,
            CHANGE);
}

std::shared_ptr<Button::State>
Button::getState()
{
    return state_;
}

void
Button::setDial()
{
    state_->dial = analogRead(Pin::dial);
}

void
Button::setJoystickUp()
{
    state_->joystick_up = !static_cast<bool>(digitalRead(Pin::joystick_up));
}

void
Button::setJoystickDown()
{
    state_->joystick_down = !static_cast<bool>(digitalRead(Pin::joystick_down));
}

void
Button::setJoystickLeft()
{
    state_->joystick_left = !static_cast<bool>(digitalRead(Pin::joystick_left));
}

void
Button::setJoystickRight()
{
    state_->joystick_right = !static_cast<bool>(digitalRead(Pin::joystick_right));
}

void
Button::setJoystickClick()
{
    state_->joystick_click = !static_cast<bool>(digitalRead(Pin::joystick_click));
}

void
Button::setPushbuttonLeft()
{
    state_->pushbutton_left = !static_cast<bool>(digitalRead(Pin::pushbutton_left));
}

void
Button::setPushbuttonRight()
{
    state_->pushbutton_right = !static_cast<bool>(digitalRead(Pin::pushbutton_right));
}
}   // namespace pixel
