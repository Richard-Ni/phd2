//
// Created by nilicheng on 23-2-16.
//
#include "Logger.h"
#include <syslog.h>

namespace remote {
namespace sdk {
namespace logger {

Logger::Logger(std::string name) {
  this->name_ = name;
  this->option_ = LOG_PID | LOG_PERROR;
  this->facility_ = LOG_LOCAL6;
  this->log2console_ = true;
  openlog(name.c_str(), this->option_, this->facility_);
}

Logger::~Logger() {
  closelog();
}

void Logger::Debug(const char *format, ...) {
  va_list ap;
  va_start(ap, format);
  vsyslog(LOG_DEBUG, format, ap);
  va_end(ap);
}

void Logger::Info(const char *format, ...) {
  va_list ap;
  va_start(ap, format);
  vsyslog(LOG_INFO, format, ap);
  va_end(ap);
}

void Logger::Notice(const char *format, ...) {
  va_list ap;
  va_start(ap, format);
  vsyslog(LOG_NOTICE, format, ap);
  va_end(ap);
}

void Logger::Warning(const char *format, ...) {
  va_list ap;
  va_start(ap, format);
  vsyslog(LOG_WARNING, format, ap);
  va_end(ap);
}

void Logger::Error(const char *format, ...) {
  va_list ap;
  va_start(ap, format);
  vsyslog(LOG_ERR, format, ap);
  va_end(ap);
}

void Logger::Critical(const char *format, ...) {
  va_list ap;
  va_start(ap, format);
  vsyslog(LOG_CRIT, format, ap);
  va_end(ap);
}

void Logger::Alert(const char *format, ...) {
  va_list ap;
  vsyslog(LOG_ALERT, format, ap);
  va_end(ap);
}

void Logger::Emerg(const char *format, ...) {
  va_list ap;
  va_start(ap, format);
  vsyslog(LOG_EMERG, format, ap);
  va_end(ap);
}

}// namespace logger
} // namespace sdk
} // namespace remote
