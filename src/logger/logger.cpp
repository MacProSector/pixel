/*
 * logger.cpp
 *
 *  Created on: Nov 19, 2021
 *      Author: simonyu
 */
#include "../devices/esp32.h"
#include "../logger/logger.h"

namespace kano_pixel_kit
{
Logger::Logger(HardwareSerial* serial)
{
    serial_ = serial;
}

void
Logger::initialize()
{
    setLogLevel(LogLevel::debug);
    serial_->begin(static_cast<int>(ESP32Serial::baud_rate));
}

void
Logger::setLogLevel(const LogLevel &log_level)
{
    log_level_ = log_level;
}

void
Logger::logError(const std::string &log)
{
    if (log_level_ >= LogLevel::error)
    {
        serial_->println(("[ERROR]: " + log + ".").c_str());
    }
}

void
Logger::logWarn(const std::string &log)
{
    if (log_level_ >= LogLevel::warn)
    {
        serial_->println(("[WARN]: " + log + ".").c_str());
    }
}

void
Logger::logInfo(const std::string &log)
{
    if (log_level_ >= LogLevel::info)
    {
        serial_->println(("[INFO]: " + log + ".").c_str());
    }
}

void
Logger::logDebug(const std::string &log)
{
    if (log_level_ >= LogLevel::debug)
    {
        serial_->println(("[DEBUG]: " + log + ".").c_str());
    }
}

void
Logger::newLine()
{
    serial_->println("");
}
} // namespace kano_pixel_kit