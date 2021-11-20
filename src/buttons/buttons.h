/*
 * buttons.h
 *
 *  Created on: Nov 20, 2021
 *      Author: simonyu
 */
#ifndef SRC_KANO_PIXEL_KIT_BUTTONS_BUTTONS_H_
#define SRC_KANO_PIXEL_KIT_BUTTONS_BUTTONS_H_

#include <memory>

namespace kano_pixel_kit
{
class Logger;

class Buttons
{
public:

    struct States
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
        States() :
                dial(0), joystick_up(false), joystick_down(false), joystick_left(
                false), joystick_right(false), joystick_click(false), pushbutton_left(
                false), pushbutton_right(false)
        {
        }
    };

    Buttons();

    void
    initialize(const std::shared_ptr<Logger> logger);

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

    static std::shared_ptr<States> states_;

private:

    std::shared_ptr<Logger> logger_;
};
} // namespace kano_pixel_kit

#endif /* SRC_KANO_PIXEL_KIT_BUTTONS_BUTTONS_H_ */