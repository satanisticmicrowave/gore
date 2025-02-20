/*
 * Copyright 2025-02-20 10:17:07 satanisticmicrowave. All rights reserved.
 *
 * Local engine clock
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-02-20 10:17:07
 * File: include/core/time/local_clock.hpp
 *
 * Made with love :3
 */

#ifndef TIME_LOCAL_CLOCK_H
#define TIME_LOCAL_CLOCK_H

#include <chrono>
#include <mutex>
#include <sstream>

#include "core/time/basic_clock.hpp"

/*
 * Class local_clock [DEFAULT]
 */

class local_clock final {
public:
  explicit local_clock() noexcept;

  DEFAULT_CLOCK_DURATION get_internal_time() noexcept;

  void scale_speed(float scale) noexcept;
  void set_time(std::chrono::steady_clock::time_point time) noexcept;

  float get_speed() noexcept;
  const std::string to_string() const noexcept;

  friend std::ostringstream &operator<<(std::ostringstream &oss,
                                        const local_clock &clock) noexcept {
    oss << clock._clock;
    return oss;
  };

private:
  basic_clock<DEFAULT_CLOCK_DURATION> _clock;
  mutable std::mutex _mtx;
};

#endif // !TIME_LOCAL_CLOCK_H
