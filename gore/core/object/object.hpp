/*
 * Copyright 2025-04-08 21:05:29 satanisticmicrowave. All rights reserved.
 *
 * The object type is needed to ensure safe and convenient work
 * with classes inside the GORE engine
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-04-08 21:05:29
 * File: gore/core/object/object.hpp
 *
 * Made with love :3
 */

#ifndef OBJECT_OBJECT_H
#define OBJECT_OBJECT_H

#include "identificator.hpp"
#include <source_location>

namespace gore::core::object {

/*
 * Class object [ABSTRACT]
 */

template <typename _derived> class object {
public:
  using id = identificator<_derived>;

  explicit object(_derived *_obj, const std::source_location location =
                                      std::source_location::current()) noexcept
      : _id(id::create(_obj, location)) {};

  id get_id() noexcept { return this->_id; };

private:
  id _id;
};

} // namespace gore::core::object

#endif // !OBJECT_OBJECT_H
