/**
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-06-21 19:09:55
 * Package: src/time/include/gore/time/clock/lazy_clock.hpp
 *
 * --
 *
 * ~ gore
 */

#ifndef GORE_LAZY_CLOCK_HPP_522195
#define GORE_LAZY_CLOCK_HPP_522195

#include <atomic>
#include <chrono>

namespace gore::time {

class lazy_clock final {
public:
  using ret_time = std::chrono::milliseconds;

  explicit lazy_clock() noexcept;

  [[nodiscard("lazy_clock::get_last_time() - returned value is ignored")]]
  ret_time get_last_time() const noexcept;

  [[nodiscard("lazy_clock::get_current_time() - returned value is ignored")]]
  ret_time get_current_time() noexcept;

private:
  std::atomic<ret_time> time;
  const std::chrono::steady_clock::time_point time_created =
      std::chrono::steady_clock::now();
};

} // namespace gore::time

#endif // GORE_LAZY_CLOCK_HPP_522195
