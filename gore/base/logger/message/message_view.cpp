/*
 * Copyright 2025-02-21 15:07:55 satanisticmicrowave. All rights reserved.
 *
 * Message view declaration
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-02-21 15:07:55
 * File: gore/base/logger/message/message_view.cpp
 *
 * Made with love :3
 */

#include "message_view.h"

#include <fmt/base.h>
#include <fmt/color.h>
#include <sstream>
#include <string>

gore::logger::message_view::color::color(C_CODE fg, C_CODE bg) noexcept {
  _style = fmt::fg(fmt::rgb(fg)) | fmt::bg(fmt::rgb(bg));
}

gore::logger::message_view::color::color(C_CODE fg) noexcept {
  _style = fmt::fg(fmt::rgb(fg));
}

std::string
gore::logger::message_view::color::operator()(std::string str_view) noexcept {
  std::ostringstream oss;
  oss << fmt::format(_style, "{}", str_view);

  return oss.str();
}

gore::logger::message_view::style::style(bool bold, bool italic) noexcept {
  if (bold) {
    _style = _style | fmt::emphasis::bold;
  }

  if (italic) {
    _style = _style | fmt::emphasis::italic;
  }
}

std::string
gore::logger::message_view::style::operator()(std::string str_view) noexcept {
  std::ostringstream oss;
  oss << fmt::format(_style, "{}", str_view);

  return oss.str();
}

std::string
gore::logger::message_view::text::operator()(std::string str_view) noexcept {
  return _style(_color(str_view));
}
