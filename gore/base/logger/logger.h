/*
 * Copyright 2025-02-21 16:34:36 satanisticmicrowave. All rights reserved.
 *
 * Logger end interface
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-02-21 16:34:36
 * File: gore/base/logger/logger.h
 *
 * Made with love :3
 */

#ifndef LOGGER_LOGGER_H
#define LOGGER_LOGGER_H

#include "message/message.h"

#include <string>

namespace gore::logger {

/*
 * Class logger [DEFAULT]
 */

class logger {
public:
  explicit logger() noexcept {};

  void log(const basic_message &message, std::string title,
           std::string text = "") noexcept;
};

}; // namespace gore::logger

#endif // !LOGGER_LOGGER_H
