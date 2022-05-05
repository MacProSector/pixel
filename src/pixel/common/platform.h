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
enum Platform
{
    cpu_cores = 2,
    analog_max = 4095
};

enum PlatformNeoPixel
{
    height = 8,
    width = 16,
    size = 128,
    value_max = 255,
    brightness_min = 10,
    brightness_max = 30
};

enum PlatformSerial
{
    baud_rate = 115200
};
} // namespace kano_pixel_kit

#endif /* SRC_KANO_PIXEL_KIT_DEVICES_ESP32_H_ */
