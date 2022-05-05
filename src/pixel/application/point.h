/*
 * point.h
 *
 *  Created on: Nov 20, 2021
 *      Author: simonyu
 */
#ifndef SRC_KANO_PIXEL_KIT_APPLICATIONS_POINT_H_
#define SRC_KANO_PIXEL_KIT_APPLICATIONS_POINT_H_

#include "application/application.h"

namespace kano_pixel_kit
{
class Point : public Application
{
public:

    Point(std::shared_ptr<Buttons> buttons, std::shared_ptr<Display> display,
            std::shared_ptr<Logger> logger);

    void
    initialize() override;

    void
    run() override;

private:

    void
    processDial();

    void
    processJoystick();

    void
    processPushbutton();

    Eigen::Vector3i color_dial_;
    Eigen::Vector3i color_buttons_;
    int pixel_index_dial_;
    int pixel_index_buttons_;
    bool set_display_frame_;
};
} // namespace kano_pixel_kit

#endif /* SRC_KANO_PIXEL_KIT_APPLICATIONS_POINT_H_ */
