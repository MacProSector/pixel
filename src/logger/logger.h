/*
 * logger.h
 *
 *  Created on: Nov 19, 2021
 *      Author: simonyu
 */
#ifndef SRC_KANO_PIXEL_KIT_LOGGER_LOGGER_H_
#define SRC_KANO_PIXEL_KIT_LOGGER_LOGGER_H_

#include <HardwareSerial.h>
#include <memory>

namespace kano_pixel_kit
{
class Logger
{
public:

    enum class LogLevel : int
    {
        error = 0,
        warn,
        info,
        debug
    };

    Logger(HardwareSerial* serial);

    void
    initialize();

    void
    setLogLevel(const LogLevel &log_level);

    void
    logError(const std::string &log);

    void
    logWarn(const std::string &log);

    void
    logInfo(const std::string &log);

    void
    logDebug(const std::string &log);

    void
    newLine();

private:

    LogLevel log_level_;
    HardwareSerial* serial_;
};
} // namespace kano_pixel_kit

#endif /* SRC_KANO_PIXEL_KIT_LOGGER_LOGGER_H_ */