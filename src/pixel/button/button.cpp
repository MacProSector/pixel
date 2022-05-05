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
#include "button/button_state.h"
#include "common/pin.h"
#include "utility/interrupt.h"
#include "utility/logger.h"

namespace pixel
{
Button::Button()
{
}

void
Button::initialize(std::shared_ptr<Logger> logger)
{
    logger_ = logger;
    button_state_ = std::make_shared<ButtonState>();

    pinMode(digitalPinToInterrupt(Pin::dial), INPUT);
    pinMode(digitalPinToInterrupt(Pin::joystick_up), INPUT);
    pinMode(digitalPinToInterrupt(Pin::joystick_down), INPUT);
    pinMode(digitalPinToInterrupt(Pin::joystick_left), INPUT);
    pinMode(digitalPinToInterrupt(Pin::joystick_right), INPUT);
    pinMode(digitalPinToInterrupt(Pin::joystick_click), INPUT);
    pinMode(digitalPinToInterrupt(Pin::pushbutton_left), INPUT);
    pinMode(digitalPinToInterrupt(Pin::pushbutton_right), INPUT);

    onJoystickUpChange();
    onJoystickDownChange();
    onJoystickLeftChange();
    onJoystickRightChange();
    onJoystickClickChange();
    onPushbuttonLeftChange();
    onPushbuttonRightChange();

    update();

    attachInterrupt(digitalPinToInterrupt(Pin::joystick_up), joystickUpInterruptHandler, CHANGE);
    attachInterrupt(digitalPinToInterrupt(Pin::joystick_down), joystickDownInterruptHandler,
    CHANGE);
    attachInterrupt(digitalPinToInterrupt(Pin::joystick_left), joystickLeftInterruptHandler,
    CHANGE);
    attachInterrupt(digitalPinToInterrupt(Pin::joystick_right), joystickRightInterruptHandler,
    CHANGE);
    attachInterrupt(digitalPinToInterrupt(Pin::joystick_click), joystickClickInterruptHandler,
    CHANGE);
    attachInterrupt(digitalPinToInterrupt(Pin::pushbutton_left), pushbuttonLeftInterruptHandler,
    CHANGE);
    attachInterrupt(digitalPinToInterrupt(Pin::pushbutton_right), pushbuttonRightInterruptHandler,
    CHANGE);
}

std::shared_ptr<ButtonState>
Button::getButtonState()
{
    return button_state_;
}

void
Button::onJoystickUpChange()
{
    button_state_->joystick_up = !static_cast<bool>(digitalRead(Pin::joystick_up));
}

void
Button::onJoystickDownChange()
{
    button_state_->joystick_down = !static_cast<bool>(digitalRead(Pin::joystick_down));
}

void
Button::onJoystickLeftChange()
{
    button_state_->joystick_left = !static_cast<bool>(digitalRead(Pin::joystick_left));
}

void
Button::onJoystickRightChange()
{
    button_state_->joystick_right = !static_cast<bool>(digitalRead(Pin::joystick_right));
}

void
Button::onJoystickClickChange()
{
    button_state_->joystick_click = !static_cast<bool>(digitalRead(Pin::joystick_click));
}

void
Button::onPushbuttonLeftChange()
{
    button_state_->pushbutton_left = !static_cast<bool>(digitalRead(Pin::pushbutton_left));
}

void
Button::onPushbuttonRightChange()
{
    button_state_->pushbutton_right = !static_cast<bool>(digitalRead(Pin::pushbutton_right));
}

void
Button::update()
{
    readDial();
}

void
Button::readDial()
{
    button_state_->dial = analogRead(Pin::dial);
}
}   // namespace pixel
