/*
 * launchpad.h
 *
 *  Created on: Nov 30, 2021
 *      Author: simonyu
 */
#ifndef SRC_KANO_PIXEL_KIT_APPLICATIONS_LAUNCHPAD_H_
#define SRC_KANO_PIXEL_KIT_APPLICATIONS_LAUNCHPAD_H_

#include "../applications/application.h"

namespace kano_pixel_kit
{
class LaunchPad : public Application
{
public:

    LaunchPad(std::shared_ptr<Buttons> buttons, std::shared_ptr<Display> display,
            std::shared_ptr<Logger> logger);

    void
    addApplication(std::shared_ptr<Application> application);

    void
    addService(std::shared_ptr<Application> service);

    void
    initialize() override;

    void
    run() override;

private:

    void
    processJoystick();

    void
    processPushbutton();

    std::shared_ptr<Application> application_;

    std::vector<std::shared_ptr<Application>> applications_;
    std::vector<std::shared_ptr<Application>> services_;

    int application_index_;
    bool application_initialized_;
    bool application_launched_;
    bool timer_started_;
    unsigned long timer_start_;
    unsigned long timer_end_;
};
} // namespace kano_pixel_kit

#endif /* SRC_KANO_PIXEL_KIT_APPLICATIONS_LAUNCHPAD_H_ */