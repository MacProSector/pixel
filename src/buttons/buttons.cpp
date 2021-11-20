/*
 * buttons.cpp
 *
 *  Created on: Nov 20, 2021
 *      Author: simonyu
 */
#include <Arduino.h>

#include "../buttons/buttons.h"
#include "../devices/esp32.h"
#include "../logger/logger.h"

namespace kano_pixel_kit
{
Buttons::Buttons()
{
}

void
Buttons::initialize(std::shared_ptr<Logger> logger)
{
    logger_ = logger;

    pinMode(digitalPinToInterrupt(static_cast<int>(ESP32Pin::dial)), INPUT);
    pinMode(digitalPinToInterrupt(static_cast<int>(ESP32Pin::joystick_up)), INPUT);
    pinMode(digitalPinToInterrupt(static_cast<int>(ESP32Pin::joystick_down)), INPUT);
    pinMode(digitalPinToInterrupt(static_cast<int>(ESP32Pin::joystick_left)), INPUT);
    pinMode(digitalPinToInterrupt(static_cast<int>(ESP32Pin::joystick_right)), INPUT);
    pinMode(digitalPinToInterrupt(static_cast<int>(ESP32Pin::joystick_click)), INPUT);
    pinMode(digitalPinToInterrupt(static_cast<int>(ESP32Pin::pushbutton_left)), INPUT);
    pinMode(digitalPinToInterrupt(static_cast<int>(ESP32Pin::pushbutton_right)), INPUT);

    setDial();
    setJoystickUp();
    setJoystickDown();
    setJoystickLeft();
    setJoystickRight();
    setJoystickClick();
    setPushbuttonLeft();
    setPushbuttonRight();

    attachInterrupt(digitalPinToInterrupt(static_cast<int>(ESP32Pin::joystick_up)), Buttons::setJoystickUp, CHANGE);
    attachInterrupt(digitalPinToInterrupt(static_cast<int>(ESP32Pin::joystick_down)), Buttons::setJoystickDown, CHANGE);
    attachInterrupt(digitalPinToInterrupt(static_cast<int>(ESP32Pin::joystick_left)), Buttons::setJoystickLeft, CHANGE);
    attachInterrupt(digitalPinToInterrupt(static_cast<int>(ESP32Pin::joystick_right)), Buttons::setJoystickRight, CHANGE);
    attachInterrupt(digitalPinToInterrupt(static_cast<int>(ESP32Pin::joystick_click)), Buttons::setJoystickClick, CHANGE);
    attachInterrupt(digitalPinToInterrupt(static_cast<int>(ESP32Pin::pushbutton_left)), Buttons::setPushbuttonLeft, CHANGE);
    attachInterrupt(digitalPinToInterrupt(static_cast<int>(ESP32Pin::pushbutton_right)), Buttons::setPushbuttonRight, CHANGE);
}

std::shared_ptr<Buttons::States>
Buttons::getStates()
{
    return std::make_shared<Buttons::States>(*states_);
}

void
Buttons::setDial()
{
    states_->dial = static_cast<int>(analogRead(static_cast<int>(ESP32Pin::dial)));
}

void
Buttons::setJoystickUp()
{
    states_->joystick_up = !static_cast<bool>(digitalRead(static_cast<int>(ESP32Pin::joystick_up)));
}

void
Buttons::setJoystickDown()
{
    states_->joystick_down = !static_cast<bool>(digitalRead(static_cast<int>(ESP32Pin::joystick_down)));
}

void
Buttons::setJoystickLeft()
{
    states_->joystick_left = !static_cast<bool>(digitalRead(static_cast<int>(ESP32Pin::joystick_left)));
}

void
Buttons::setJoystickRight()
{
    states_->joystick_right = !static_cast<bool>(digitalRead(static_cast<int>(ESP32Pin::joystick_right)));
}

void
Buttons::setJoystickClick()
{
    states_->joystick_click = !static_cast<bool>(digitalRead(static_cast<int>(ESP32Pin::joystick_click)));
}

void
Buttons::setPushbuttonLeft()
{
    states_->pushbutton_left = !static_cast<bool>(digitalRead(static_cast<int>(ESP32Pin::pushbutton_left)));
}

void
Buttons::setPushbuttonRight()
{
    states_->pushbutton_right = !static_cast<bool>(digitalRead(static_cast<int>(ESP32Pin::pushbutton_right)));
}
} // namespace kano_pixel_kit