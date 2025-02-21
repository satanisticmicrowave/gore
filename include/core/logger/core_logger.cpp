/*
 * Copyright 2025-02-21 17:31:32 satanisticmicrowave. All rights reserved.
 *
 * Core logger interface
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-02-21 17:31:32
 * File: include/core/logger/core_logger.cpp
 *
 * Made with love :3
 */

#include "core_logger.hpp"
#include "../../../gore/base/logger/message/basic_message.h"

#include <string>

/*
 * Add information to logger message
 */

std::string core_logger::fetch(const gore::logger::basic_message &message,
                               std::string title, std::string text) noexcept {
  std::string log;

  _clock.update_clock();

  if (text == "") {
    log = message.format(_clock.to_string(), title);
  } else {
    log = message.format(_clock.to_string(), title, text);
  }

  return log;
}

core_logger::core_logger() noexcept {}
core_logger::~core_logger() noexcept {}
