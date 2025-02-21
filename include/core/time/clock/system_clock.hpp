/*
 * Copyright 2025-02-20 09:50:15 satanisticmicrowave. All rights reserved.
 *
 * Global engine clock
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-02-20 09:50:15
 * File: include/core/time/system_clock.hpp
 *
 * Made with love :3
 */

#ifndef TIME_SYSTEM_CLOCK_H
#define TIME_SYSTEM_CLOCK_H

#include "core/time/clock/basic_clock.hpp"

#include <mutex>
#include <sstream>

/*
 * Class system_clock [DEFAULT]
 */

class system_clock final {
public:
  explicit system_clock() noexcept;

  DEFAULT_CLOCK_DURATION get_current_time() noexcept;
  DEFAULT_CLOCK_DURATION get_last_time() noexcept;

  void scale_speed(float scale) noexcept;
  void update_clock() noexcept;

  float get_speed() noexcept;
  const std::string to_string() const noexcept;

  friend std::ostringstream &operator<<(std::ostringstream &oss,
                                        const system_clock &clock) noexcept {
    oss << clock._clock;
    return oss;
  };

private:
  static basic_clock<DEFAULT_CLOCK_DURATION> _clock;
  static std::mutex _mtx;
};

#endif // !TIME_SYSTEM_CLOCK_H
