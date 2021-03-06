/*
 *  Copyright (C) 2022  Simon Yu
 *
 *  Developed by:   Simon Yu (yujunda@icloud.com)
 *                  https://www.simonyu.net/
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

/**
 *  @file   logger.cpp
 *  @author Simon Yu
 *  @date   11/19/2021
 *  @brief  Logger class source.
 *
 *  This file implements the logger class.
 */

/*
 *  External headers.
 */
#include <Arduino.h>

/*
 *  Project headers.
 */
#include "common/platform.h"
#include "utility/logger.h"

/*
 *  pixel namespace.
 */
namespace pixel
{
Logger::Logger() : log_level_(LogLevel::debug), status_(LogLevel::debug)
{
    /*
     *  Initialize the platform serial connection
     *  at the baud rate defined in the PlatformSerial enum.
     */
    Serial.begin(PlatformSerial::baud_rate);
}

Logger::LogLevel
Logger::getStatus() const
{
    /*
     *  Return the status log level.
     */
    return status_;
}

void
Logger::setLogLevel(const LogLevel &log_level)
{
    /*
     *  Set the log level.
     */
    log_level_ = log_level;
}

void
Logger::logRaw(const std::string &log)
{
    /*
     *  Validate Arduino Serial object.
     */
    if (Serial)
    {
        if (log == "")
        {
            /*
             *  Prints new line if the message is empty.
             */
            Serial.println();
        }
        else
        {
            /*
             *  Prints the message as is with new line.
             */
            Serial.println(log.c_str());
        }
    }
}

void
Logger::logError(const std::string &log)
{
    /*
     *  Validate Arduino Serial object and check log level.
     */
    if (Serial && log_level_ >= LogLevel::error)
    {
        if (log == "")
        {
            /*
             *  Prints new line if the message is empty.
             */
            Serial.println();
        }
        else
        {
            /*
             *  Prints the message in error format
             *  with new line and period.
             */
            Serial.println(("[ERROR]: " + log + ".").c_str());

            /*
             *  Set the status log level to error if it's not already error.
             */
            if (status_ != LogLevel::error)
            {
                status_ = LogLevel::error;
            }
        }
    }
}

void
Logger::logWarn(const std::string &log)
{
    /*
     *  Validate Arduino Serial object and check log level.
     */
    if (Serial && log_level_ >= LogLevel::warn)
    {
        if (log == "")
        {
            /*
             *  Prints new line if the message is empty.
             */
            Serial.println();
        }
        else
        {
            /*
             *  Prints the message in warning format
             *  with new line and period.
             */
            Serial.println(("[WARN]: " + log + ".").c_str());

            /*
             *  Set the status log level to warn if it's
             *  not already warn and not already error.
             */
            if (status_ != LogLevel::warn && status_ != LogLevel::error)
            {
                status_ = LogLevel::warn;
            }
        }
    }
}

void
Logger::logInfo(const std::string &log)
{
    /*
     *  Validate Arduino Serial object and check log level.
     */
    if (Serial && log_level_ >= LogLevel::info)
    {
        if (log == "")
        {
            /*
             *  Prints new line if the message is empty.
             */
            Serial.println();
        }
        else
        {
            /*
             *  Prints the message in information format
             *  with new line and period.
             */
            Serial.println(("[INFO]: " + log + ".").c_str());
        }
    }
}

void
Logger::logDebug(const std::string &log)
{
    /*
     *  Validate Arduino Serial object and check log level.
     */
    if (Serial && log_level_ >= LogLevel::debug)
    {
        if (log == "")
        {
            /*
             *  Prints new line if the message is empty.
             */
            Serial.println();
        }
        else
        {
            /*
             *  Prints the message in debugging format
             *  with new line and period.
             */
            Serial.println(("[DEBUG]: " + log + ".").c_str());
        }
    }
}
}   // namespace pixel
