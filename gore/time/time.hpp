/*
 * Copyright 2025-04-09 12:31:18 satanisticmicrowave. All rights reserved.
 *
 * Base concepts and core of time module
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-04-09 12:31:18
 * File: gore/time/time.hpp
 *
 * Made with love :3
 */

#ifndef TIME_TIME_H
#define TIME_TIME_H

#include <chrono>
#include <type_traits>

namespace gore::time {

template <typename T>
concept clock_duration = std::is_base_of_v<std::chrono::nanoseconds, T> ||
                         std::is_base_of_v<std::chrono::milliseconds, T> ||
                         std::is_base_of_v<std::chrono::seconds, T> ||
                         std::is_base_of_v<std::chrono::minutes, T> ||
                         std::is_base_of_v<std::chrono::hours, T>;
} // namespace gore::time

#endif // !TIME_TIME_H
