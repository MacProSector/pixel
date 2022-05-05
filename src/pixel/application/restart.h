/*
 * restart.h
 *
 *  Created on: Nov 20, 2021
 *      Author: simonyu
 */
#ifndef SRC_KANO_PIXEL_KIT_APPLICATIONS_RESTART_H_
#define SRC_KANO_PIXEL_KIT_APPLICATIONS_RESTART_H_

#include "application/application.h"

namespace kano_pixel_kit
{
class Restart : public Application
{
public:

    Restart(std::shared_ptr<Button> button, std::shared_ptr<Display> display,
            std::shared_ptr<Logger> logger);

    void
    initialize() override;

    void
    run() override;

private:

    void
    displayRestartScreen();

    bool timer_started_;
    unsigned long timer_start_;
    unsigned long timer_end_;
};
} // namespace kano_pixel_kit

#endif /* SRC_KANO_PIXEL_KIT_APPLICATIONS_RESTART_H_ */
