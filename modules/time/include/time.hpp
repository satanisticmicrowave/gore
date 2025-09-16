/**
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-09-14 01:20:24
 * Package: modules/time/include/time.hpp
 *
 * Time module
 *
 * ~ gore
 */

#ifndef GORE_TIME_HPP_802024
#define GORE_TIME_HPP_802024

#include "clock.hpp"

namespace gore::time {

inline clock::scaled_clock<double, std::milli> &default_clock() noexcept {
  static clock::scaled_clock<double, std::milli> instance;
  return instance;
}

} // namespace gore::time

#endif // GORE_TIME_HPP_802024
