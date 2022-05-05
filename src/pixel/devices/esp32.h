/*
 * esp32.h
 *
 *  Created on: Nov 19, 2021
 *      Author: simonyu
 */
#ifndef SRC_KANO_PIXEL_KIT_DEVICES_ESP32_H_
#define SRC_KANO_PIXEL_KIT_DEVICES_ESP32_H_

namespace kano_pixel_kit
{
enum class ESP32Pin : int
{
    neo_pixel = 4,
    pushbutton_right = 18,
    pushbutton_left = 23,
    joystick_right = 25,
    joystick_left = 26,
    joystick_click = 27,
    joystick_down = 34,
    joystick_up = 35,
    dial = 36
};

enum class ESP32Platform : int
{
    cpu_cores = 2,
    analog_max = 4095
};

enum class ESP32Serial : int
{
    baud_rate = 115200
};
} // namespace kano_pixel_kit

#endif /* SRC_KANO_PIXEL_KIT_DEVICES_ESP32_H_ */
