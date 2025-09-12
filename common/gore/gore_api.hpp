/**
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-09-12 23:17:09
 * Package: common/dllexport.hpp
 *
 * Add symbol export
 *
 * ~ gore
 */

#ifndef GORE_DLLEXPORT_HPP_708229
#define GORE_DLLEXPORT_HPP_708229

#if defined(_WIN32) || defined(__CYGWIN__)
#ifdef GORE_EXPORTS
#define GORE_API __declspec(dllexport)
#else
#define GORE_API __declspec(dllimport)
#endif
#elif __GNUC__ >= 4
#define GORE_API __attribute__((visibility("default")))
#else
#define GORE_API
#endif

#endif // GORE_DLLEXPORT_HPP_708229
