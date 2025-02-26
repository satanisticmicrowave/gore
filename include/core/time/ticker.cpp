/*
 * Copyright 2025-02-26 16:47:52 satanisticmicrowave. All rights reserved.
 *
 * TPS balance system
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-02-26 16:47:52
 * File: include/core/time/ticker.cpp
 *
 * Made with love :3
 */

#include "ticker.hpp"
#include <chrono>

ticker::ticker(callable &&callable, double tps) noexcept {
  _tick_payload = callable;
  set_tps(tps);

  _active = false;
}

ticker::~ticker() noexcept { join(); }

/*
 * Set ticker tps
 */

void ticker::set_tps(double tps) noexcept {
  _tps.store(tps);

  _duration = std::chrono::duration_cast<std::chrono::steady_clock::duration>(
      std::chrono::milliseconds(
          static_cast<int>(1000 / _tps.load() / _clock.get_speed())));

  _time = std::chrono::steady_clock::now() - _duration;
}

/*
 * Set tick payload
 */

void ticker::set_tick_payload(callable &&callable) noexcept {
  _tick_payload = callable;
}

/*
 * Start ticker
 */

void ticker::start() noexcept {
  while (!_active.exchange(true)) {
    _active.store(true);
    _worker = std::thread([this]() { tick(); });
  }
}

/*
 * Stop ticker
 */

void ticker::stop() noexcept {
  _active.store(false);
  join();
}

/*
 * Join thread
 */

void ticker::join() noexcept {
  if (_worker.joinable()) {
    _worker.join();
  }
}

/*
 * Tick system
 */

void ticker::tick() {
  while (_active.load()) {

    _duration = std::chrono::steady_clock::duration(std::chrono::milliseconds(
        static_cast<int>((1000 / _tps.load()) / _clock.get_speed())));

    std::chrono::steady_clock::time_point current =
        std::chrono::steady_clock::now();

    std::chrono::steady_clock::duration elapsed = current - _time;

    if (elapsed >= _duration) {
      _time = current;
      _tick_payload();

      std::chrono::steady_clock::duration sleep =
          _duration - (std::chrono::steady_clock::now() - current);

      if (sleep > std::chrono::steady_clock::duration::zero()) {
        std::this_thread::sleep_for(sleep);
      }
    } else {
      std::this_thread::sleep_until(_time + _duration);
    }
  }
}

/*
 * Return ticker tps
 */

double ticker::get_tps() noexcept { return _tps.load(); }

/*
 * Return pointer to internal ticker clock
 */

local_clock *ticker::get_internal_clock() noexcept { return &_clock; }
