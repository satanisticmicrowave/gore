/*
 * Copyright 2025-04-09 12:28:43 satanisticmicrowave. All rights reserved.
 *
 * Asbtract clock, base of time module in engine
 * System clock - global time from program is started
 * Local clock - time from this clock is created
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-04-09 12:28:43
 * File: include/time/basic_clock.hpp
 *
 * Made with love :3
 */

#ifndef TIME_BASIC_CLOCK_H
#define TIME_BASIC_CLOCK_H

#include "../../gore/core/object/object.hpp"
#include "../../gore/time/time.hpp"
#include <ostream>
#include <source_location>
#include <sstream>

/*
 * Class basic_clock [ABSTRACT]
 */

template <typename _derived, gore::time::clock_duration _dur>
class basic_clock : public gore::core::object::object<_derived> {
public:
  explicit basic_clock(_derived *_obj,
                       const std::source_location &location =
                           std::source_location::current()) noexcept
      : gore::core::object::object<_derived>(_obj, location) {};

  virtual _dur get_real_time() noexcept = 0;
  virtual _dur get_internal_time() noexcept = 0;
  virtual _dur get_last_used_time() const noexcept = 0;

  virtual void scale_speed(double scale_factor) noexcept = 0;
  virtual void set_time(_dur time) noexcept = 0;

  virtual double get_speed() const noexcept = 0;
  virtual std::string to_string() const noexcept = 0;

  friend std::ostringstream &
  operator<<(std::ostringstream &oss,
             const basic_clock<_derived, _dur> &_clock) noexcept {
    oss << _clock.to_string();

    return oss;
  }

  friend std::ostream &
  operator<<(std::ostream &os,
             const basic_clock<_derived, _dur> &_clock) noexcept {
    if (os) {
      os << _clock.to_string();
    }

    return os;
  }
};

#endif // !TIME_BASIC_CLOCK_H
