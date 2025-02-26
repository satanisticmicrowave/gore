/*
 * Copyright 2025-02-26 18:32:00 satanisticmicrowave. All rights reserved.
 *
 * --
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-02-26 18:32:00
 * File: gore/test/ticker.cpp
 *
 * Made with love :3
 */

#include "ticker.h"
#include "../../include/core/time/ticker.hpp"
#include <iostream>
#include <thread>

using namespace std::chrono_literals;

void ticker_test() noexcept {

  int count = 0;

  ticker ticker([&count]() { count++; }, 10);
  ticker.start();

  std::this_thread::sleep_for(10s);
  std::cout << "[10 TPS; 1 SPEED; 10S] 100 = " << count << std::endl;
  ticker.stop();

  ticker.get_internal_clock()->scale_speed(2.0f);
  ticker.start();
  std::this_thread::sleep_for(10s);
  std::cout << "[10 TPS; 2 SPEED; 10S] 300 = " << count << std::endl;
  ticker.stop();

  ticker.get_internal_clock()->scale_speed(0.5f);
  ticker.start();
  std::this_thread::sleep_for(10s);
  std::cout << "[10 TPS; 0.5 SPEED; 10S] 350 = " << count << std::endl;
  ticker.stop();
}
