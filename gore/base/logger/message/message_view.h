/*
 * Copyright 2025-02-21 14:16:41 satanisticmicrowave. All rights reserved.
 *
 * Message view declaration
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-02-21 14:16:41
 * File: gore/base/logger/message/message_view.h
 *
 * Made with love :3
 */

#ifndef MESSAGE_MESSAGE_VIEW_H
#define MESSAGE_MESSAGE_VIEW_H

#include <cstdint>
#include <fmt/color.h>
#include <string>

#define C_CODE const uint32_t
#define C_STYLE fmt::text_style

namespace gore::logger::message_view {

/*
 * Color view
 */

struct color final {
  explicit color(C_CODE fg, C_CODE bg) noexcept;
  explicit color(C_CODE fg) noexcept;

  std::string operator()(std::string str_view) noexcept;

  C_STYLE _style;
};

/*
 * Format view
 */

struct style final {

  explicit style(bool bold, bool italic) noexcept;

  std::string operator()(std::string str_view) noexcept;

  C_STYLE _style;
};

/*
 * Combine style and color
 */

struct text final {

  std::string operator()(std::string str_view) noexcept;

  style _style;
  color _color;
};

}; // namespace gore::logger::message_view

#endif // !MESSAGE_MESSAGE_VIEW_H
