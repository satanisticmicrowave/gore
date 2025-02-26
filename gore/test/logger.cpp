/*
 * Copyright 2025-02-21 17:52:32 satanisticmicrowave. All rights reserved.
 *
 * Logger test
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-02-21 17:52:32
 * File: gore/test/logger.cpp
 *
 * Made with love :3
 */

#include "logger.h"

#include "../base/logger/logger.h"
#include <thread>

using namespace std::chrono_literals;

void logger_test() {

  gore::logger::logger logger;

  logger.log(gore::logger::message::INFO, "Info text!");
  std::this_thread::sleep_for(123ms);

  logger.log(gore::logger::message::WARNING,
             "Warning! This test unexpectly working!", "Hehe.");
  std::this_thread::sleep_for(1399ms);

  logger.log(gore::logger::message::ERROR, "Aww, error!", "*error*");
  std::this_thread::sleep_for(5634ms);

  logger.log(gore::logger::message::FATAL, "!!! FATAL ERROR !!!",
             "Please, kill yourself.");
}
