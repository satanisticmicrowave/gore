/*
 * Copyright 2025-02-20 10:01:02 satanisticmicrowave. All rights reserved.
 *
 * Global engine clock
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-02-20 10:01:02
 * File: include/core/time/system_clock.cpp
 *
 * Made with love :3
 */

#include "core/time/clock/system_clock.hpp"
#include "core/time/clock/basic_clock.hpp"

#include <mutex>

basic_clock<DEFAULT_CLOCK_DURATION> system_clock::_clock =
    basic_clock<DEFAULT_CLOCK_DURATION>();

std::mutex system_clock::_mtx = std::mutex();

system_clock::system_clock() noexcept {}

DEFAULT_CLOCK_DURATION system_clock::get_current_time() noexcept {
  std::lock_guard<std::mutex> lock(_mtx);

  return _clock.get_current_time();
}

DEFAULT_CLOCK_DURATION system_clock::get_last_time() noexcept {
  std::lock_guard<std::mutex> lock(_mtx);

  return _clock.get_last_time();
}

void system_clock::scale_speed(float scale) noexcept {
  std::lock_guard<std::mutex> lock(_mtx);

  _clock.scale_speed(scale);
}

const std::string system_clock::to_string() const noexcept {
  std::lock_guard<std::mutex> lock(_mtx);

  return _clock.to_string();
}
