/**
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-07-29 15:50:38
 * Package: modules/time/include/clock.hpp
 *
 * ~ gore

 */

#ifndef GORE_CLOCK_HPP_793438
#define GORE_CLOCK_HPP_793438

#include <chrono>
#include <gore/gore_api.hpp>
#include <mutex>
#include <type_traits>

namespace gore::time::clock {

template <typename _rep, typename _period> struct GORE_API scaled_clock {
  using rep = _rep;
  using period = _period;
  using duration = std::chrono::duration<rep, period>;
  using time_point = std::chrono::time_point<scaled_clock>;
  using basic_clock = std::chrono::steady_clock;

  static_assert(std::is_floating_point_v<rep>,
                "Clock rep must be floating point");

  scaled_clock();
  time_point now() const;
  void set_scale(rep scale);

private:
  mutable std::mutex _mutex;
  basic_clock::time_point _last_update;
  duration _scaled_time;
  rep _scale;
};

} // namespace gore::time::clock

#endif // GORE_CLOCK_HPP_793438
