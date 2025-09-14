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
#include <gore/autoexec.hpp>
#include <gore/gore_api.hpp>

namespace gore::time {

GORE_API GORE_AUTOEXEC inline clock::scaled_clock<double, std::milli> &
default_clock() noexcept {
  static clock::scaled_clock<double, std::milli> instance;
  return instance;
}

} // namespace gore::time

#endif // GORE_TIME_HPP_802024
