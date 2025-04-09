/*
 * Copyright 2025-04-08 22:02:31 satanisticmicrowave. All rights reserved.
 *
 * Crash function for unexpected situations
 * Engine's suicide note
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-04-08 22:02:31
 * File: gore/core/exception/crash.hpp
 *
 * Made with love :3
 */

#ifndef EXCEPTION_CRASH_H
#define EXCEPTION_CRASH_H

#include <exception>
#include <format>
#include <iostream>
#include <source_location>
#include <string>

namespace gore::core::exception {

inline void
crash(std::string message,
      const std::source_location &location = std::source_location::current()) {

  std::set_terminate([]() { std::abort(); });

  std::cerr << std::format(
                   "\nGore core crashed!\n---\n{}\nFile: {}\nLine: {}:{}",
                   message, location.file_name(), location.line(),
                   location.column())
            << std::endl;

  std::terminate();
}

} // namespace gore::core::exception

#endif // !EXCEPTION_CRASH_H
