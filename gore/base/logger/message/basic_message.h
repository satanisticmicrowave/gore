/*
 * Copyright 2025-02-21 14:12:24 satanisticmicrowave. All rights reserved.
 *
 * Logger message basic class
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-02-21 14:12:24
 * File: gore/base/logger/message/basic_message.h
 *
 * Made with love :3
 */

#include "message_view.h"

#include <format>
#include <sstream>
#include <string>

#ifndef MESSAGE_BASIC_MESSAGE_H
#define MESSAGE_BASIC_MESSAGE_H

namespace gore::logger {

/*
 * Class basic_message [DEFAULT]
 */

class basic_message {
public:
  using MESSAGE_TEXT = message_view::text;
  using TYPE_DESCRIPTOR = std::string;

  /*
   * Cloroize and format string
   */

  std::string format(std::string time, std::string title) const noexcept {
    std::ostringstream oss;

    oss << fmt::format("[{}] {} - {}\n", time,
                       _type()(std::format("[{}]", _descriptor())),
                       _title()(std::format("{}", title)));

    return oss.str();
  }

  /*
   * Cloroize and format string
   */

  std::string format(std::string time, std::string title,
                     std::string text) const noexcept {
    std::ostringstream oss;

    oss << format(time, title) << _text()(std::format(" ---\n{}\n\n", text));

    return oss.str();
  }

  std::string log(std::string time, std::string title) const noexcept {
    std::ostringstream oss;

    oss << fmt::format("[{}] {} - {}\n", time,
                       std::format("[{}]", _descriptor()),
                       std::format("{}", title));

    return oss.str();
  };

  std::string log(std::string time, std::string title,
                  std::string text) const noexcept {
    std::ostringstream oss;

    oss << log(time, title) << std::format(" ---\n{}\n\n", text);

    return oss.str();
  }

protected:
  virtual TYPE_DESCRIPTOR _descriptor() const noexcept = 0;

  virtual MESSAGE_TEXT _title() const noexcept = 0;
  virtual MESSAGE_TEXT _text() const noexcept = 0;
  virtual MESSAGE_TEXT _type() const noexcept = 0;
};

}; // namespace gore::logger

#endif // !MESSAGE_BASIC_MESSAGE_H
