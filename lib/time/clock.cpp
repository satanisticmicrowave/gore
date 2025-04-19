/*
 * Copyright 2025-04-14 05:53:47 satanisticmicrowave. All rights reserved.
 *
 * GORE time module clock API
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-04-14 05:53:47
 * File: lib/time/clock.cpp
 *
 * Made with love :3
 */

#include "../../gore/time/clock.hpp"
#include "../../include/time/gore_clock.hpp"
#include <chrono>

namespace gore::time {

clock *main_clock = new clock;

clock *create_clock() noexcept { return new clock(); }

template <clock_duration _duration>
_duration get_real_time(clock *_clock) noexcept {
  return std::chrono::duration_cast<_duration>(
      std::chrono::steady_clock::now() - _clock->get_created_time());
}

template <clock_duration _duration>
_duration get_internal_time(clock *_clock) noexcept {
  update_clock(_clock);
  return std::chrono::duration_cast<_duration>(_clock->get_internal_time());
}

float get_clock_speed(clock *_clock) noexcept {
  return _clock->get_scale_factor();
}

void set_clock_speed(float speed, clock *_clock) noexcept {
  _clock->set_scale_factor(speed);
}

void update_clock(clock *_clock) noexcept {

  std::chrono::steady_clock::duration real =
      std::chrono::steady_clock::now() - _clock->get_created_time();

  std::chrono::steady_clock::duration delta = real - _clock->get_last_time();

  std::chrono::steady_clock::duration internal =
      std::chrono::duration_cast<std::chrono::steady_clock::duration>(
          delta * _clock->get_scale_factor());

  _clock->set_last_time(real);
  _clock->set_internal_time(_clock->get_internal_time() + internal);
}

template std::chrono::nanoseconds get_real_time(clock *);
template std::chrono::milliseconds get_real_time(clock *);
template std::chrono::seconds get_real_time(clock *);
template std::chrono::minutes get_real_time(clock *);
template std::chrono::hours get_real_time(clock *);

template std::chrono::nanoseconds get_internal_time(clock *);
template std::chrono::milliseconds get_internal_time(clock *);
template std::chrono::seconds get_internal_time(clock *);
template std::chrono::minutes get_internal_time(clock *);
template std::chrono::hours get_internal_time(clock *);

} // namespace gore::time
