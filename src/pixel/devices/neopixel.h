/*
 * neo_pixel.h
 *
 *  Created on: Nov 19, 2021
 *      Author: simonyu
 */
#ifndef SRC_KANO_PIXEL_KIT_DEVICES_NEO_PIXEL_H_
#define SRC_KANO_PIXEL_KIT_DEVICES_NEO_PIXEL_H_

namespace kano_pixel_kit
{
enum class NeoPixel : int
{
    height = 8,
    width = 16,
    size = 128,
    value_max = 255,
    brightness_min = 10,
    brightness_max = 30
};
} // namespace kano_pixel_kit

#endif /* SRC_KANO_PIXEL_KIT_DEVICES_NEO_PIXEL_H_ */
