/*
 * Copyright 2025-02-26 16:31:29 satanisticmicrowave. All rights reserved.
 *
 * TPS balance system
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-02-26 16:31:29
 * File: include/core/time/ticker.hpp
 *
 * Made with love :3
 */

#ifndef TIME_TICKER_H
#define TIME_TICKER_H

#include "clock/local_clock.hpp"

#include <atomic>
#include <functional>
#include <thread>

/*
 * Class ticker [DEFAULT]
 */

class ticker {
public:
  using callable = std::function<void()>;

  explicit ticker(callable &&callable = []() {}, double tps = 120) noexcept;
  ~ticker() noexcept;

  void set_tps(double tps) noexcept;
  void set_tick_payload(callable &&calable) noexcept;

  double get_tps() noexcept;

  void join() noexcept;

  void start() noexcept;
  void stop() noexcept;

  local_clock *get_internal_clock() noexcept;

private:
  std::atomic<double> _tps;
  std::atomic_bool _active;

  callable _tick_payload;

  std::thread _worker;

  std::chrono::steady_clock::time_point _time;
  std::chrono::steady_clock::duration _duration;
  local_clock _clock;

  void tick();
};

#endif // !TIME_TICKER_H
