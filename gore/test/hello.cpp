/*
 * Copyright 2025-02-18 14:00:28 satanisticmicrowave. All rights reserved.
 *
 * Hello world test header
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-02-18 14:00:28
 * File: gore/test/hello.cpp
 *
 * Made with love :3
 */

#include "hello.h"

#include <fmt/color.h>
#include <iostream>

void hello() {
  std::cout << fmt::format(fg(fmt::rgb(153, 255, 153)), "Hello, world!")
            << std::endl;
}
