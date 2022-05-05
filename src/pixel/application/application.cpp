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

    for (int i = 0; i < static_cast<int>(PlatformNeoPixel::size); i ++)
    {
        display_frame_->push_back(Eigen::Vector3i(0, 0, 0));
    }

    for (int i = 0; i < static_cast<int>(PlatformNeoPixel::size); i ++)
    {
        // Default white border
        if (i < static_cast<int>(PlatformNeoPixel::width)
                || i > static_cast<int>(PlatformNeoPixel::size) - static_cast<int>(PlatformNeoPixel::width)
                || i % static_cast<int>(PlatformNeoPixel::width) == 0
                || i % static_cast<int>(PlatformNeoPixel::width) == static_cast<int>(PlatformNeoPixel::width) - 1)
        {
            display_frame_splash_->push_back(
                    Eigen::Vector3i(static_cast<int>(PlatformNeoPixel::value_max),
                            static_cast<int>(PlatformNeoPixel::value_max),
                            static_cast<int>(PlatformNeoPixel::value_max)));
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
