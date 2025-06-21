/**
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-06-21 19:10:31
 * Package: src/time/src/clock/lazy_clock.cpp
 *
 * ~ gore
 */

#include "../../include/gore/time/clock/lazy_clock.hpp"

namespace gore::time {

lazy_clock::lazy_clock() noexcept { this->time.store(ret_time::zero()); }

std::chrono::milliseconds lazy_clock::get_last_time() const noexcept {
  return this->time.load();
}

std::chrono::milliseconds lazy_clock::get_current_time() noexcept {
  auto delta = std::chrono::steady_clock::now() - this->time_created;
  this->time.store(std::chrono::duration_cast<ret_time>(delta));

  return this->get_last_time();
}

} // namespace gore::time
