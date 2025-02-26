/*
 * Copyright 2025-02-24 02:50:08 satanisticmicrowave. All rights reserved.
 *
 * Shutdown game
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-02-24 02:50:08
 * File: include/utility/shutdown_invoker.hpp
 *
 * Made with love :3
 */

#ifndef UTILITY_SHUTDOWN_INVOKER_H
#define UTILITY_SHUTDOWN_INVOKER_H

#include <functional>
#include <vector>

/*
 * Class shutdown_invoker [DEFAULT]
 */

class shutdown_invoker final {
public:
  using shutdown_callback = std::function<void()>;

  static void shutdown(int code) noexcept;
  static void on_shutdown(shutdown_callback &&callback) noexcept;

private:
  static std::vector<shutdown_callback> _callbacks;
};

#endif // !UTILITY_SHUTDOWN_INVOKER_H
