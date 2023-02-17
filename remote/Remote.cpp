#include "sdk/log/Logger.h"
#include "Remote.h"
#include "server/server.h"

namespace remote {

} // namespace remote

int main() {
  auto l = remote::sdk::logger::Logger("remote");
  l.Debug("Debug %d", 2023);
  l.Error("Error %d", 2023);
  l.Info("Info %d", 2023);
  l.Notice("Notice %d", 2023);
  auto s = remote::Server("0.0.0.0", 9999);
  s.Run();
}
