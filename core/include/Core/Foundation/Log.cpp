#include "Core/Foundation/Log.hpp"
#include <iostream>

namespace Core {
void Log(LogLevel lvl, const std::string &msg) {
  const char *tag = (lvl == LogLevel::Trace)  ? "TRACE"
                    : (lvl == LogLevel::Info) ? "INFO"
                    : (lvl == LogLevel::Warn) ? "WARN"
                                              : "ERROR";
  std::cout << "[" << tag << "] " << msg << "\n";
}
} // namespace Core
