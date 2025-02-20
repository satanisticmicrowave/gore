/*
 * Copyright 2025-02-20 08:06:36 satanisticmicrowave. All rights reserved.
 *
 * Core integration component of clock
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-02-20 08:06:36
 * File: include/core/time/basic_clock.hpp
 *
 * Made with love :3
 */

#ifndef TIME_BASIC_CLOCK_H
#define TIME_BASIC_CLOCK_H

#include <chrono>
#include <sstream>
#include <string>
#include <type_traits>

template <typename T>
concept duration = std::is_same_v<T, std::chrono::nanoseconds> ||
                   std::is_same_v<T, std::chrono::milliseconds> ||
                   std::is_same_v<T, std::chrono::seconds> ||
                   std::is_same_v<T, std::chrono::minutes> ||
                   std::is_same_v<T, std::chrono::hours>;

using DEFAULT_CLOCK_DURATION = std::chrono::milliseconds;

namespace {

inline std::string convert_ds(double value, int min_digits) {

  std::ostringstream ss;
  ss << value;

  std::string value_s = ss.str();
  int digits = min_digits - value_s.size();

  if (digits > 0) {
    value_s = std::string(digits, '0') + value_s;
  }

  return value_s;
}

} // namespace

/*
 * Class basic_clock [TEMPLATE]
 */

template <duration _dur> class basic_clock final {
public:
  explicit basic_clock() noexcept {
    _time_created = std::chrono::steady_clock::now();
    _time_last = _dur::zero();
    _time = _dur::zero();

    _time_scale = 1;
  };

  /*
   * Return current time without scale
   */

  _dur get_current_time() noexcept {
    return std::chrono::duration_cast<_dur>(std::chrono::steady_clock::now() -
                                            _time_created);
  };

  /*
   * Return internal time with scale
   */

  _dur get_internal_time() noexcept {
    _dur realtime = get_current_time();
    auto changed_time = (realtime - _time_last) * _time_scale;

    _time += changed_time;
    _time_last = realtime;

    return get_last_time();
  };

  /*
   * Return last used time
   */

  _dur get_last_time() noexcept {
    return std::chrono::duration_cast<_dur>(_time);
  };

  /*
   * Set scale speed
   */

  void scale_speed(float scale) noexcept { _time_scale = scale; };

  /*
   * Set current time
   */

  void set_time(std::chrono::steady_clock::time_point time) noexcept {
    _time_created = time;
    _time_last = _dur::zero();
    _time = _dur::zero();
  };

  /*
   * Get clock speed
   */

  float get_speed() noexcept { return _time_scale; };

  /*
   * Return string with time
   */

  const std::string to_string() const noexcept {
    std::chrono::milliseconds milliseconds =
        std::chrono::duration_cast<std::chrono::milliseconds>(_time);

    std::chrono::seconds seconds =
        std::chrono::duration_cast<std::chrono::seconds>(milliseconds);
    milliseconds -= seconds;

    std::chrono::minutes minutes =
        std::chrono::duration_cast<std::chrono::minutes>(seconds);
    seconds -= minutes;

    std::chrono::hours hours =
        std::chrono::duration_cast<std::chrono::hours>(minutes);
    minutes -= hours;

    std::string time_str = std::format(
        "{}:{}:{}:{}", convert_ds(hours.count(), 3),
        convert_ds(minutes.count(), 2), convert_ds(seconds.count(), 2),
        convert_ds(milliseconds.count(), 3));

    return time_str;
  };

  friend std::ostringstream &
  operator<<(std::ostringstream &oss, const basic_clock<_dur> &clock) noexcept {
    oss << clock.to_string();
    return oss;
  };

private:
  std::chrono::steady_clock::time_point _time_created;
  std::chrono::steady_clock::duration _time_last;
  std::chrono::steady_clock::duration _time;

  float _time_scale;
};

#endif // !TIME_BASIC_CLOCK_H
