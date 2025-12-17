#pragma once
#include <string>

namespace Core {
enum class LogLevel { Trace, Info, Warn, Error };

void Log(LogLevel lvl, const std::string &msg);
} // namespace Core
