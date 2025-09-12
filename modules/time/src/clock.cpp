/**
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-09-12 23:52:20
 * Package: modules/time/src/clock.cpp
 *
 * ~ gore
 */

#include "../include/clock.hpp"

namespace gore::time::clock {

template <typename rep, typename period>
scaled_clock<rep, period>::scaled_clock()
    : _last_update(basic_clock::now()), _scaled_time(duration::zero()),
      _scale(1.0) {}

template <typename rep, typename period>
typename scaled_clock<rep, period>::time_point
scaled_clock<rep, period>::now() const {
  std::lock_guard lock(_mutex);
  const auto current_time = basic_clock::now();
  const auto real_duration = current_time - _last_update;
  const auto scaled_duration = real_duration * _scale;
  return time_point{_scaled_time +
                    std::chrono::duration_cast<duration>(scaled_duration)};
}

template <typename rep, typename period>
void scaled_clock<rep, period>::set_scale(rep scale) {
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

// Явные инстанцирования для конкретных типов
template struct GORE_API scaled_clock<float, std::milli>;
template struct GORE_API scaled_clock<double, std::milli>;

} // namespace gore::time::clock
