/*
 * Copyright 2025-02-21 17:19:44 satanisticmicrowave. All rights reserved.
 *
 * Core logger interface
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-02-21 17:19:44
 * File: include/core/logger/core_logger.hpp
 *
 * Made with love :3
 */

#ifndef LOGGER_CORE_LOGGER_H
#define LOGGER_CORE_LOGGER_H

#include "../../../gore/base/logger/message/basic_message.h"
#include "core/time/clock/system_clock.hpp"

#include <string>

/*
 * Class core_logger [DEFAULT]
 */

class core_logger {
public:
  static core_logger &instance() {
    static core_logger instance;
    return instance;
  };

  std::string fetch(const gore::logger::basic_message &message,
                    std::string title, std::string text = "") noexcept;

private:
  explicit core_logger() noexcept;
  ~core_logger() noexcept;

  core_logger(const core_logger &) = delete;
  core_logger &operator=(const core_logger &) = delete;

  system_clock _clock;
};

#endif // !LOGGER_CORE_LOGGER_H
