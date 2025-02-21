/*
 * Copyright 2025-02-21 17:46:48 satanisticmicrowave. All rights reserved.
 *
 * Logger end interface
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-02-21 17:46:48
 * File: gore/base/logger/logger.cpp
 *
 * Made with love :3
 */

#include "logger.h"
#include "core/logger/core_logger.hpp"

#include <iostream>
#include <string>

namespace gore::logger {

/*
 * Log message
 */

void logger::log(const basic_message &message, std::string title,
                 std::string text) noexcept {
  std::cout << core_logger::instance().fetch(message, title, text);
}

}; // namespace gore::logger
