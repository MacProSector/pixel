/*
 * application.cpp
 *
 *  Created on: Nov 30, 2021
 *      Author: simonyu
 */
#include "../applications/application.h"
#include "../devices/neopixel.h"

namespace kano_pixel_kit
{
Application::Application(std::shared_ptr<Buttons> buttons, std::shared_ptr<Display> display,
        std::shared_ptr<Logger> logger)
{
    buttons_ = buttons;
    display_ = display;
    logger_ = logger;

    buttons_state_ = buttons_->getStates();
    display_frame_ = std::make_shared<std::vector<Eigen::Vector3i>>();
    display_frame_splash_ = std::make_shared<std::vector<Eigen::Vector3i>>();

    for (int i = 0; i < static_cast<int>(NeoPixel::size); i ++)
    {
        display_frame_->push_back(Eigen::Vector3i(0, 0, 0));
    }

    for (int i = 0; i < static_cast<int>(NeoPixel::size); i ++)
    {
        // Default white border
        if (i < static_cast<int>(NeoPixel::width) ||
            i > static_cast<int>(NeoPixel::size) - static_cast<int>(NeoPixel::width) ||
            i % static_cast<int>(NeoPixel::width) == 0 ||
            i % static_cast<int>(NeoPixel::width) == static_cast<int>(NeoPixel::width) - 1)
        {
            display_frame_splash_->push_back(Eigen::Vector3i(255, 255, 255));
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