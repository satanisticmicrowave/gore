/*
 * Copyright 2025-02-21 16:38:36 satanisticmicrowave. All rights reserved.
 *
 * Pre-defined message types
 *
 * Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
 * Date: 2025-02-21 16:38:36
 * File: gore/base/logger/message/message.h
 *
 * Made with love :3
 */

#ifndef MESSAGE_MESSAGE_H
#define MESSAGE_MESSAGE_H

#include "basic_message.h"
#include "message_view.h"

namespace gore::logger::message {

class info_message : public basic_message {
private:
  virtual TYPE_DESCRIPTOR _descriptor() const noexcept override {
    return "INFO";
  };

  virtual MESSAGE_TEXT _type() const noexcept override {
    return {message_view::style(true, true), message_view::color(0x42aaff)};
  }

  virtual MESSAGE_TEXT _title() const noexcept override {
    return {message_view::style(false, true), message_view::color(0x00bfff)};
  }

  virtual MESSAGE_TEXT _text() const noexcept override {
    return {message_view::style(false, false), message_view::color(0x00bfff)};
  };
};

class warning_message : public basic_message {
private:
  virtual TYPE_DESCRIPTOR _descriptor() const noexcept override {
    return "WARNING";
  };

  virtual MESSAGE_TEXT _type() const noexcept override {
    return {message_view::style(true, false),
            message_view::color(0x000000, 0xffd800)};
  }

  virtual MESSAGE_TEXT _title() const noexcept override {
    return {message_view::style(true, false), message_view::color(0xffd800)};
  }

  virtual MESSAGE_TEXT _text() const noexcept override {
    return {message_view::style(false, true), message_view::color(0xffd800)};
  };
};

class error_message : public basic_message {
private:
  virtual TYPE_DESCRIPTOR _descriptor() const noexcept override {
    return "ERROR";
  };

  virtual MESSAGE_TEXT _type() const noexcept override {
    return {message_view::style(true, true), message_view::color(0xff2400)};
  }

  virtual MESSAGE_TEXT _title() const noexcept override {
    return {message_view::style(true, false), message_view::color(0xff0000)};
  }

  virtual MESSAGE_TEXT _text() const noexcept override {
    return {message_view::style(true, false), message_view::color(0xff0000)};
  };
};

class fatal_message : public basic_message {
private:
  virtual TYPE_DESCRIPTOR _descriptor() const noexcept override {
    return "FATAL";
  };

  virtual MESSAGE_TEXT _type() const noexcept override {
    return {message_view::style(true, false),
            message_view::color(0xffffff, 0xff2400)};
  }

  virtual MESSAGE_TEXT _title() const noexcept override {
    return {message_view::style(true, true), message_view::color(0xff2400)};
  }

  virtual MESSAGE_TEXT _text() const noexcept override {
    return {message_view::style(true, false), message_view::color(0xff2400)};
  };
};

inline const basic_message &INFO = info_message();
inline const basic_message &WARNING = warning_message();
inline const basic_message &ERROR = error_message();
inline const basic_message &FATAL = fatal_message();

}; // namespace gore::logger::message

#endif // !MESSAGE_MESSAGE_H
