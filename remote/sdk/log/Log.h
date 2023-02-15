//
// Created by nilicheng on 23-2-16.
//

#ifndef PHD2_REMOTE_SDK_LOG_LOG_H_
#define PHD2_REMOTE_SDK_LOG_LOG_H_

#include <string>
#include "Logger.h"
namespace remote {
namespace sdk {
namespace logger {

const int LevelTrace = 0;
const int LevelDebug = 1;
const int LevelInfo = 2;
const int LevelWarn = 3;
const int LevelError = 4;

class Log {
 public:
  Log(Logger *logger);
  Log *Trace();
  Log *Debug();
  Log *Info();
  Log *Warn();
  Log *Error();
  Log *Message(const std::string &msg);
  Log *Messagef(const char *format, ...);
  ~Log();
 private:
  int level_;
  Logger *logger_;
  std::string content_;
};

} // namespace logger
} // namespace sdk
} // namespace remote

#endif // PHD2_REMOTE_SDK_LOG_LOG_H_
