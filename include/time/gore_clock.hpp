/*
 * Copyright 2025-04-14 05:25:57 satanisticmicrowave. All rights reserved.
 *
 * Lazy access to game time.
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-04-14 05:25:57
 * File: include/time/gore_clock.hpp
 *
 * Made with love :3
 */

#ifndef TIME_GORE_CLOCK_H
#define TIME_GORE_CLOCK_H

#include <chrono>
#include <mutex>

namespace gore::time {

/*
 * Class clock [DEFAULT]
 */

class clock {
public:
  using _clock = std::chrono::steady_clock;

  explicit clock() noexcept {
    _created_time = _clock::now();
    _last_time = _clock::duration::zero();
    _internal_time = _clock::duration::zero();

    _scale_factor = 1.0f;
  }

  void set_last_time(_clock::duration last_time) noexcept {
    std::lock_guard<std::mutex> lock(_mtx);

    _last_time = last_time;
  }

  void set_internal_time(_clock::duration internal_time) noexcept {
    std::lock_guard<std::mutex> lock(_mtx);

    _internal_time = internal_time;
  }

  void set_scale_factor(float scale_factor) noexcept {
    std::lock_guard<std::mutex> lock(_mtx);

    _scale_factor = scale_factor;
  }

  _clock::time_point get_created_time() const noexcept { return _created_time; }

  _clock::duration get_last_time() const noexcept { return _last_time; };
  _clock::duration get_internal_time() const noexcept { return _internal_time; }

  float get_scale_factor() const noexcept { return _scale_factor; }

private:
  _clock::time_point _created_time;
  _clock::duration _last_time;
  _clock::duration _internal_time;

  float _scale_factor;

  std::mutex _mtx;
};

} // namespace gore::time

#endif // !TIME_GORE_CLOCK_H
