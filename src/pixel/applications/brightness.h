/*
 * brightness.h
 *
 *  Created on: Nov 30, 2021
 *      Author: simonyu
 */
#ifndef SRC_KANO_PIXEL_KIT_APPLICATIONS_BRIGHTNESS_H_
#define SRC_KANO_PIXEL_KIT_APPLICATIONS_BRIGHTNESS_H_

#include "../applications/application.h"

namespace kano_pixel_kit
{
class Brightness : public Application
{
public:

    Brightness(std::shared_ptr<Buttons> buttons, std::shared_ptr<Display> display,
            std::shared_ptr<Logger> logger);

    void
    initialize() override;

    void
    run() override;

private:

    void
    processDial();

    void
    displayBrightness();

    Eigen::Vector3i color_;
    int brightness_value_;
    bool initialized_;
};
} // namespace kano_pixel_kit

#endif /* SRC_KANO_PIXEL_KIT_APPLICATIONS_BRIGHTNESS_H_ */