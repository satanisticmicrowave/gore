/*
 * Copyright 2025-02-20 10:23:50 satanisticmicrowave. All rights reserved.
 *
 * Local engine clock
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-02-20 10:23:50
 * File: include/core/time/local_clock.cpp
 *
 * Made with love :3
 */

#include "core/time/local_clock.hpp"
#include "core/time/basic_clock.hpp"
#include <chrono>
#include <mutex>

local_clock::local_clock() noexcept {
  _clock = basic_clock<DEFAULT_CLOCK_DURATION>();
}

DEFAULT_CLOCK_DURATION local_clock::get_internal_time() noexcept {
  std::lock_guard<std::mutex> lock(_mtx);

  return _clock.get_internal_time();
}

void local_clock::scale_speed(float scale) noexcept {
  std::lock_guard<std::mutex> lock(_mtx);

  _clock.scale_speed(scale);
}

void local_clock::set_time(
    std::chrono::steady_clock::time_point time) noexcept {
  std::lock_guard<std::mutex> lock(_mtx);

  _clock.set_time(time);
}

float local_clock::get_speed() noexcept {
  std::lock_guard<std::mutex> lock(_mtx);

  return _clock.get_speed();
}

const std::string local_clock::to_string() const noexcept {
  std::lock_guard<std::mutex> lock(_mtx);

  return _clock.to_string();
}
