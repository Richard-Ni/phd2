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
  this->option_ = 0;
  this->facility_ = LOG_LOCAL6;
  openlog(name.c_str(), this->option_, this->facility_);
}

Logger::~Logger() {
  closelog();
}
void Logger::Send(int level, std::string content) {
  syslog(level, "%s\n", content.c_str());
}
}// namespace logger
} // namespace sdk
} // namespace remote
