/*
 * Copyright 2025-04-14 04:57:12 satanisticmicrowave. All rights reserved.
 *
 * GORE time module clock API
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-04-14 04:57:12
 * File: gore/time/clock.hpp
 *
 * Made with love :3
 */

#ifndef TIME_CLOCK_H
#define TIME_CLOCK_H

#include "time.hpp"
#include <chrono>

namespace gore::time {

/*
 * gore::time::clock
 * Default clock location: gore::time::main_clock
 * Provides lazy loading of the current in-game time in two ways:
 *
 * Real Time:
 * Monotonous time since the clock was created, not subject to distortion due to
 * the set rate
 *
 * In-game time:
 * Time subject to distortion by the speed of the clock.
 *
 * Recommended: Use real time for external debugging or counting real values,
 * and internal time for in-game calculations
 */

class clock;
extern clock *main_clock;

clock *create_clock() noexcept;

template <clock_duration _duration = std::chrono::milliseconds>
_duration get_real_time(clock *_clock = main_clock) noexcept;

template <clock_duration _duration = std::chrono::milliseconds>
_duration get_internal_time(clock *_clock = main_clock) noexcept;

float get_clock_speed(clock *_clock) noexcept;
void set_clock_speed(float speed, clock *_clock) noexcept;

void update_clock(clock *_clock) noexcept;

} // namespace gore::time

#endif // !TIME_CLOCK_H
