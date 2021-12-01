/*
 * display.h
 *
 *  Created on: Nov 19, 2021
 *      Author: simonyu
 */
#ifndef SRC_KANO_PIXEL_KIT_DISPLAY_DISPLAY_H_
#define SRC_KANO_PIXEL_KIT_DISPLAY_DISPLAY_H_

#include <Adafruit_NeoPixel.h>
#include <ArduinoEigenDense.h>
#include <memory>
#include <mutex>
#include <vector>

namespace kano_pixel_kit
{
class Logger;

class Display
{
public:

    Display();

    void
    initialize(std::shared_ptr<Logger> logger);

    bool
    lock();

    void
    unlock();

    void
    setBrightness(const int &brightness);

    void
    setFrame(std::shared_ptr<std::vector<Eigen::Vector3i>> frame);

    bool
    setFrameAtomic(std::shared_ptr<std::vector<Eigen::Vector3i>> frame);

    void
    clear();

private:

    void
    displayStartScreen();

    Adafruit_NeoPixel neopixel_;

    std::shared_ptr<Logger> logger_;
    std::shared_ptr<std::vector<Eigen::Vector3i>> frame_;

    std::unique_lock<std::mutex> lock_;
    std::mutex mutex_;
    unsigned long timer_start_;
    unsigned long timer_end_;
};
} // namespace kano_pixel_kit

#endif /* SRC_KANO_PIXEL_KIT_DISPLAY_DISPLAY_H_ */