/*
 * point.h
 *
 *  Created on: Nov 20, 2021
 *      Author: simonyu
 */
#ifndef SRC_KANO_PIXEL_KIT_APPLICATIONS_POINT_H_
#define SRC_KANO_PIXEL_KIT_APPLICATIONS_POINT_H_

#include <ArduinoEigenDense.h>
#include <memory>
#include <vector>

#include "../buttons/buttons.h"

namespace kano_pixel_kit
{
class Display;
class Logger;

class Point
{
public:

    Point();

    void
    initialize(std::shared_ptr<Buttons> buttons, std::shared_ptr<Display> display,
        std::shared_ptr<Logger> logger);

    void
    run();

private:

    std::shared_ptr<Buttons> buttons_;
    std::shared_ptr<Display> display_;
    std::shared_ptr<Logger> logger_;

    std::shared_ptr<Buttons::States> states_;
    std::shared_ptr<std::vector<Eigen::Vector3i>> frame_;

    Eigen::Vector3i color_dial_;
    Eigen::Vector3i color_buttons_;

    int pixel_index_dial_;
    int pixel_index_buttons_;

    bool timer_started_;
    unsigned long timer_start_;
    unsigned long timer_end_;
};
} // namespace kano_pixel_kit

#endif /* SRC_KANO_PIXEL_KIT_APPLICATIONS_POINT_H_ */