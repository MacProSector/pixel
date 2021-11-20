/*
 * display.h
 *
 *  Created on: Nov 19, 2021
 *      Author: simonyu
 */
#ifndef SRC_KANO_PIXEL_KIT_DISPLAY_DISPLAY_H_
#define SRC_KANO_PIXEL_KIT_DISPLAY_DISPLAY_H_

#include <ArduinoEigenDense.h>
#include <memory>
#include <mutex>
#include <vector>

class Adafruit_NeoPixel;

namespace kano_pixel_kit
{
class Logger;

class Display
{
public:

    Display();

    void
    initialize(const std::shared_ptr<Logger> logger, const int& brightness_limit = 255);

    void
    setFrame(const std::vector<Eigen::Vector3i> &frame);

    void
    clear();

private:

    std::shared_ptr<Adafruit_NeoPixel> neopixel_;
    std::shared_ptr<Logger> logger_;
    std::mutex mutex_;
};
} // namespace kano_pixel_kit

#endif /* SRC_KANO_PIXEL_KIT_DISPLAY_DISPLAY_H_ */