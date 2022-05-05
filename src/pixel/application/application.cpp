/*
 * application.cpp
 *
 *  Created on: Nov 30, 2021
 *      Author: simonyu
 */
#include "application/application.h"
#include "common/platform.h"

namespace kano_pixel_kit
{
Application::Application(std::shared_ptr<Button> buttons, std::shared_ptr<Display> display,
        std::shared_ptr<Logger> logger)
{
    button_ = buttons;
    display_ = display;
    logger_ = logger;

    button_state_ = button_->getState();
    display_frame_ = std::make_shared<std::vector<Eigen::Vector3i>>();
    display_frame_splash_ = std::make_shared<std::vector<Eigen::Vector3i>>();

    for (int i = 0; i < PlatformNeoPixel::size; i ++)
    {
        display_frame_->push_back(Eigen::Vector3i(0, 0, 0));
    }

    for (int i = 0; i < PlatformNeoPixel::size; i ++)
    {
        // Default white border
        if (i < PlatformNeoPixel::width || i > PlatformNeoPixel::size - PlatformNeoPixel::width
                || i % PlatformNeoPixel::width == 0
                || i % PlatformNeoPixel::width == PlatformNeoPixel::width - 1)
        {
            display_frame_splash_->push_back(
                    Eigen::Vector3i(PlatformNeoPixel::value_max, PlatformNeoPixel::value_max,
                            PlatformNeoPixel::value_max));
        }
        else
        {
            display_frame_splash_->push_back(Eigen::Vector3i(0, 0, 0));
        }
    }
}

std::shared_ptr<std::vector<Eigen::Vector3i>>
Application::getSplashScreen() const
{
    return display_frame_splash_;
}
} // namespace kano_pixel_kit
