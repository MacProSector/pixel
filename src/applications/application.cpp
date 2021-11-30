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

    for (int i = 0; i < static_cast<int>(NeoPixel::size); i ++)
    {
        display_frame_->push_back(Eigen::Vector3i(0, 0, 0));
    }
}
} // namespace kano_pixel_kit