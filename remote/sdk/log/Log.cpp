//
// Created by nilicheng on 23-2-16.
//

#include "Log.h"
#include <cstdarg>

namespace remote {
namespace sdk {
namespace logger {
#define LOG_LINE_BUF_LEN 1024

Log::Log(Logger *logger) {
  this->logger_ = logger;
  this->level_ = LevelInfo;
}
Log *Log::Trace() {
  this->level_ = LevelTrace;
  return this;
}
Log *Log::Debug() {
  this->level_ = LevelDebug;
  return this;
}
Log *Log::Info() {
  this->level_ = LevelInfo;
  return this;
}
Log *Log::Warn() {
  this->level_ = LevelWarn;
  return this;
}
Log *Log::Error() {
  this->level_ = LevelError;
  return this;
}
Log *Log::Message(const std::string &msg) {
  this->content_ += msg;
  this->logger_->Send(this->level_, this->content_);
  return this;
}

Log *Log::Messagef(const char *format, ...) {
  char buf[LOG_LINE_BUF_LEN] = {0};
  va_list ap;
  va_start(ap, format);
  vsnprintf(buf, LOG_LINE_BUF_LEN, format, ap);
  va_end(ap);
  this->content_ += std::string(buf);
  this->logger_->Send(this->level_, this->content_);
  return this;
}

} // namespace logger
} // namespace sdk
} // namespace remote
