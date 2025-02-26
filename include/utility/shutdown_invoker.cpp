/*
 * Copyright 2025-02-24 02:58:43 satanisticmicrowave. All rights reserved.
 *
 * Shutdown game
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-02-24 02:58:43
 * File: include/utility/shutdown_invoker.cpp
 *
 * Made with love :3
 */

#include "shutdown_invoker.hpp"
#include "../../gore/base/logger/logger.h"

#include <cstdlib>
#include <vector>

std::vector<shutdown_invoker::shutdown_callback> shutdown_invoker::_callbacks =
    {};

/*
 * Call all callbacks and exit program
 */

void shutdown_invoker::shutdown(int code) noexcept {

  for (auto &callback : _callbacks) {
    callback();
  }

  gore::logger::logger logger;
  logger.log(gore::logger::message::INFO,
             std::format("Exiting with code {}", code));

  std::exit(code);
}

/*
 * Add shutdown callback
 */

void shutdown_invoker::on_shutdown(shutdown_callback &&callback) noexcept {
  _callbacks.emplace_back(callback);
}
