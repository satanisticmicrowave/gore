/**
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-09-14 01:39:46
 * Package: common/gore/autoexec.hpp
 *
 * Automatically execute function before main()
 *
 * ~ gore
 */

#ifndef GORE_AUTOEXEC_HPP_803186
#define GORE_AUTOEXEC_HPP_803186

#if defined(_MSC_VER)
#define GORE_AUTOEXEC                                                          \
  __pragma(section(".CRT$XCU", read))                                          \
      __declspec(allocate(".CRT$XCU")) static void __stdcall
#elif defined(__GNUC__) || defined(__clang__)
#define GORE_AUTOEXEC __attribute__((constructor))
#else
#define GORE_AUTOEXEC static
#pragma message("Warning: GORE_AUTOEXEC may not work on this compiler")
#endif

#endif // GORE_AUTOEXEC_HPP_803186
