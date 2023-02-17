//
// Created by nilicheng on 23-2-16.
//

#ifndef PHD2_REMOTE_SERVER_SERVER_H_
#define PHD2_REMOTE_SERVER_SERVER_H_

#include <string>
namespace remote {

class Server {
 public:
  Server(std::string ip, uint16_t port) {
	ip_ = ip;
	port_ = port;
  }
  int Run();
 private:
  std::string ip_;
  uint16_t port_;
};

} // namespace remote

#endif // PHD2_REMOTE_SERVER_SERVER_H_
