/*
 * logger.cpp
 *
 *  Created on: Nov 19, 2021
 *      Author: simonyu
 */
#include <Arduino.h>

#include "../devices/esp32.h"
#include "../logger/logger.h"

namespace kano_pixel_kit
{
Logger::Logger()
{
}

void
Logger::initialize()
{
    setLogLevel(LogLevel::debug);
    Serial.begin(static_cast<int>(ESP32Serial::baud_rate));
}

void
Logger::setLogLevel(const LogLevel& log_level)
{
    std::lock_guard<std::mutex> lock(mutex_);
    log_level_ = log_level;
}

void
Logger::logError(const std::string& log)
{
    if (Serial && log_level_ >= LogLevel::error)
    {
        std::lock_guard<std::mutex> lock(mutex_);

        if (log == "")
        {
            Serial.println();
        }
        else
        {
            Serial.println(("[ERROR]: " + log + ".").c_str());
        }
    }
}

void
Logger::logWarn(const std::string& log)
{
    if (Serial && log_level_ >= LogLevel::warn)
    {
        std::lock_guard<std::mutex> lock(mutex_);

        if (log == "")
        {
            Serial.println();
        }
        else
        {
            Serial.println(("[WARN]: " + log + ".").c_str());
        }
    }
}

void
Logger::logInfo(const std::string& log)
{
    if (Serial && log_level_ >= LogLevel::info)
    {
        std::lock_guard<std::mutex> lock(mutex_);

        if (log == "")
        {
            Serial.println();
        }
        else
        {
            Serial.println(("[INFO]: " + log + ".").c_str());
        }
    }
}

void
Logger::logDebug(const std::string& log)
{
    if (Serial && log_level_ >= LogLevel::debug)
    {
        std::lock_guard<std::mutex> lock(mutex_);

        if (log == "")
        {
            Serial.println();
        }
        else
        {
            Serial.println(("[DEBUG]: " + log + ".").c_str());
        }
    }
}
} // namespace kano_pixel_kit
