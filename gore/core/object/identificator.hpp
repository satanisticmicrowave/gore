/*
 * Copyright 2025-04-08 21:09:01 satanisticmicrowave. All rights reserved.
 *
 * Universal identifier for objects within the GORE engine
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-04-08 21:09:01
 * File: gore/core/object/identificator.hpp
 *
 * Made with love :3
 */

#ifndef OBJECT_IDENTIFICATOR_H
#define OBJECT_IDENTIFICATOR_H

#include "../exception/crash.hpp"

#include <bit>
#include <cstdint>
#include <format>
#include <functional>
#include <iomanip>
#include <iostream>
#include <source_location>

namespace gore::core::object {

/*
 * Class identificator [DEFAULT]
 */

template <typename _object> class identificator final {
public:
  static identificator<_object>
  create(_object *_obj, const std::source_location &location =
                            std::source_location::current()) noexcept {

    if (_obj == nullptr) {
      exception::crash(std::format("Cannot create an unique id for {}!",
                                   typeid(_object).name()),
                       location);
    }

    uintptr_t addr = std::bit_cast<uintptr_t>(_obj);
    std::hash<uintptr_t> hasher;

    return identificator(hasher(addr));
  }

  friend std::ostream &operator<<(std::ostream &os,
                                  const identificator<_object> _id) noexcept {

    if (!os) {
      return os;
    }

    os << "0x" << std::hex << std::setfill('0')
       << std::setw(sizeof(_id._id) * 2) << _id._id;

    return os;
  }

private:
  explicit identificator(size_t _id) noexcept : _id(_id) {}

  size_t _id;
};

} // namespace gore::core::object

#endif // !OBJECT_IDENTIFICATOR_H
