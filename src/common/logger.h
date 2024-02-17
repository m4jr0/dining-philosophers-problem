// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#ifndef DPP_COMMON_LOGGER_H_
#define DPP_COMMON_LOGGER_H_

#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>

#include "common/primitive.h"

// If issues arise with current terminal, comment this line.
#define DPP_TERMINAL_COLORS

#define DPP_ASCII_PREFIX "\033["
#define DPP_ASCII_SUFFIX "m"
#define DPP_ASCII_ATTR_SUFFIX ";"
#define DPP_ASCII_EMPHASIS_ATTR "1" DPP_ASCII_ATTR_SUFFIX

#define DPP_ASCII_NORMAL_COL "0"  // Default terminal color.
#define DPP_ASCII_INFO_COL DPP_ASCII_NORMAL_COL
#define DPP_ASCII_ERROR_COL "31"    // Red color.
#define DPP_ASCII_WARNING_COL "33"  // Yellow color.
#define DPP_ASCII_DEBUG_COL "90"    // Dark gray color.

#ifdef DPP_TERMINAL_COLORS
#define DPP_ASCII_CATEGORY(COLOR) \
  DPP_ASCII_PREFIX DPP_ASCII_EMPHASIS_ATTR COLOR DPP_ASCII_SUFFIX
#define DPP_ASCII(COLOR) DPP_ASCII_PREFIX COLOR DPP_ASCII_SUFFIX
#define DPP_ASCII_RESET DPP_ASCII(DPP_ASCII_NORMAL_COL)
#else
#define DPP_ASCII_CATEGORY(COLOR) ""
#define DPP_ASCII(COLOR) ""
#define DPP_ASCII_RESET ""
#endif  // DPP_TERMINAL_COLORS

namespace dpp {
class Logger final {
 public:
  static Logger& Get();

  Logger() = default;
  Logger(const Logger&) = delete;
  Logger(Logger&&) = delete;
  Logger& operator=(const Logger&) = delete;
  Logger& operator=(Logger&&) = delete;
  ~Logger() = default;

  template <typename... Targs>
  void Error(const Targs&... args) {
    std::stringstream string_stream;
    GetString(string_stream, args...);
    std::lock_guard<std::mutex> lock(output_mutex_);
    std::cerr << DPP_ASCII_CATEGORY(DPP_ASCII_ERROR_COL) << "[ERROR]"
              << DPP_ASCII(DPP_ASCII_ERROR_COL) << " " << string_stream.str()
              << DPP_ASCII_RESET << '\n';
  }

  template <typename... Targs>
  void Info(const Targs&... args) {
    std::stringstream string_stream;
    GetString(string_stream, args...);
    std::lock_guard<std::mutex> lock(output_mutex_);
    std::cout << DPP_ASCII_CATEGORY(DPP_ASCII_INFO_COL) << "[INFO]"
              << DPP_ASCII(DPP_ASCII_INFO_COL) << " " << string_stream.str()
              << DPP_ASCII_RESET << '\n';
  }

  template <typename... Targs>
  void Debug(const Targs&... args) {
    std::stringstream string_stream;
    GetString(string_stream, args...);
    std::lock_guard<std::mutex> lock(output_mutex_);
    std::cout << DPP_ASCII_CATEGORY(DPP_ASCII_DEBUG_COL) << "[DEBUG]"
              << DPP_ASCII(DPP_ASCII_DEBUG_COL) << " " << string_stream.str()
              << DPP_ASCII_RESET << '\n';
  }

  template <typename... Targs>
  void Warning(const Targs&... args) {
    std::stringstream string_stream;
    GetString(string_stream, args...);
    std::lock_guard<std::mutex> lock(output_mutex_);
    std::cout << DPP_ASCII_CATEGORY(DPP_ASCII_WARNING_COL) << "[WARNING]"
              << DPP_ASCII(DPP_ASCII_WARNING_COL) << " " << string_stream.str()
              << DPP_ASCII_RESET << '\n';
  }

 private:
  template <typename T>
  void GetString(std::stringstream& string_stream, const T& arg) const {
    string_stream << arg;
  }

  template <typename T, typename... Targs>
  void GetString(std::stringstream& string_stream, const T& arg,
                 const Targs&... args) const {
    GetString(string_stream, arg);
    GetString(string_stream, args...);
  }

  static std::unique_ptr<Logger> Generate();
  inline static std::unique_ptr<Logger> logger_{nullptr};
  std::mutex output_mutex_{};
};

#ifndef DPP_DEBUG
#define DPP_LOG_ERROR(...)
#define DPP_LOG_INFO(...)
#define DPP_LOG_DEBUG(...)
#define DPP_LOG_WARNING(...)
#else
#define DPP_LOG_ERROR(...) dpp::Logger::Get().Error(__VA_ARGS__)
#define DPP_LOG_INFO(...) dpp::Logger::Get().Info(__VA_ARGS__)
#define DPP_LOG_DEBUG(...) dpp::Logger::Get().Debug(__VA_ARGS__)
#define DPP_LOG_WARNING(...) dpp::Logger::Get().Warning(__VA_ARGS__)
#endif  // !DPP_DEBUG
}  // namespace dpp

#endif  // DPP_COMMON_LOGGER_H_
