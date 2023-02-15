//
// Created by nilicheng on 23-2-16.
//

#ifndef PHD2_REMOTE_SDK_LOG_LOGGER_H_
#define PHD2_REMOTE_SDK_LOG_LOGGER_H_

#include <string>
namespace remote {
namespace sdk {
namespace logger {
class Logger {
 public:
  Logger(std::string name);
  static void Send(int level, std::string content);
  ~Logger();
 private:
  std::string name_;
  int option_;
  int facility_;
};
}// namespace log
} // namespace sdk
} // namespace remote

#endif // PHD2_REMOTE_SDK_LOG_LOGGER_H_
