/**
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-07-29 15:50:38
 * Package: src/time/include/gore/time/clock.hpp
 *
 * ~ gore
 */

#ifndef GORE_CLOCK_HPP_793438
#define GORE_CLOCK_HPP_793438

#include <chrono>
#include <mutex>
#include <stdexcept>
#include <type_traits>

namespace gore::time::clock {

template <typename _rep, typename _period> struct scaled_clock {
  using rep = _rep;
  using period = _period;

  using duration = std::chrono::duration<rep, period>;
  using time_point = std::chrono::time_point<scaled_clock>;
  using basic_clock = std::chrono::steady_clock;

  static_assert(std::is_floating_point_v<rep>,
                "Clock rep must be floating point");

  scaled_clock()
      : _last_update(basic_clock::now()), _scaled_time(duration::zero()),
        _scale(1.0) {}

  time_point now() const {
    std::lock_guard lock(_mutex);
    const auto current_time = basic_clock::now();
    const auto real_duration = current_time - _last_update;
    const auto scaled_duration = real_duration * _scale;
    return time_point{_scaled_time +
                      std::chrono::duration_cast<duration>(scaled_duration)};
  }

  void set_scale(rep scale) {
    if (scale < 0) {
      throw std::runtime_error("Scale must be non-negative");
    }

    std::lock_guard lock(_mutex);

    const auto current_time = basic_clock::now();
    const auto real_duration = current_time - _last_update;

    const auto scaled_duration = real_duration * _scale;

    _scaled_time += std::chrono::duration_cast<duration>(scaled_duration);

    _last_update = current_time;
    _scale = scale;
  }

private:
  mutable std::mutex _mutex;
  basic_clock::time_point _last_update;
  duration _scaled_time;
  rep _scale;
};

} // namespace gore::time::clock

#endif // GORE_CLOCK_HPP_793438
