/*
 * application.h
 *
 *  Created on: Nov 30, 2021
 *      Author: simonyu
 */
#ifndef SRC_KANO_PIXEL_KIT_APPLICATIONS_APPLICATION_H_
#define SRC_KANO_PIXEL_KIT_APPLICATIONS_APPLICATION_H_

#include <ArduinoEigenDense.h>
#include <memory>
#include <vector>

#include "buttons/buttons.h"
#include "display/display.h"
#include "logger/logger.h"

namespace kano_pixel_kit
{
class Application
{
public:

    Application(std::shared_ptr<Buttons> buttons, std::shared_ptr<Display> display,
            std::shared_ptr<Logger> logger);

    virtual void
    initialize() = 0;

    virtual void
    run() = 0;

    std::shared_ptr<std::vector<Eigen::Vector3i>>
    getSplashScreen() const;

protected:

    std::shared_ptr<Buttons> buttons_;
    std::shared_ptr<Display> display_;
    std::shared_ptr<Logger> logger_;
    std::shared_ptr<Buttons::States> buttons_state_;
    std::shared_ptr<std::vector<Eigen::Vector3i>> display_frame_;
    std::shared_ptr<std::vector<Eigen::Vector3i>> display_frame_splash_;
};
} // namespace kano_pixel_kit

#endif /* SRC_KANO_PIXEL_KIT_APPLICATIONS_APPLICATION_H_ */
