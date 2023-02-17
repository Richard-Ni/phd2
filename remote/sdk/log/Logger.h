//
// Created by nilicheng on 23-2-16.
//

#ifndef PHD2_REMOTE_SDK_LOG_LOGGER_H_
#define PHD2_REMOTE_SDK_LOG_LOGGER_H_

#include <string>
#include <cstdarg>

namespace remote {
namespace sdk {
namespace logger {

class Logger {
 public:
  Logger(std::string name);
  ~Logger();
  void Error(const char *format, ...);
  void Warning(const char *format, ...);
  void Info(const char *format, ...);
  void Debug(const char *format, ...);
  void Notice(const char *format, ...);
  void Critical(const char *format, ...);
  void Alert(const char *format, ...);
  void Emerg(const char *format, ...);
 private:
  void Log(int level, const char *format, ...);
  std::string name_;
  bool log2console_;
  int option_;
  int facility_;
};
}// namespace log
} // namespace sdk
} // namespace remote

#endif // PHD2_REMOTE_SDK_LOG_LOGGER_H_
