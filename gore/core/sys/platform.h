/*
 * Copyright 2025-02-24 02:31:16 satanisticmicrowave. All rights reserved.
 *
 * Define game platform
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-02-24 02:31:16
 * File: gore/core/sys/platform.h
 *
 * Made with love :3
 */

#ifndef SYS_PLATFORM_H
#define SYS_PLATFORM_H

enum platform {
  PLATFORM_WINDOWS,
  PLATFORM_MACOS,
  PLATFORM_LINUX,
  PLATFORM_UNKNOWN
};

#if defined(_WIN32)
#define _GORE_PLATFORM "WINDOWS"
const platform GORE_PLATFORM = PLATFORM_WINDOWS;
#elif defined(__APPLE__) && defined(__MACH__)
#define _GORE_PLATFORM "MACOS"
const platform GORE_PLATFORM = PLATFORM_MACOS;
#elif defined(__linux__)
#define _GORE_PLATFORM "LINUX"
const platform GORE_PLATFORM = PLATFORM_LINUX;
#else
const platform GORE_PLATFORM = PLATFORM_UNKNOWN;
#endif

#endif // !SYS_PLATFORM_H
