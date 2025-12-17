
#pragma once
#include <string>

namespace Core {

enum class EventType {
  None = 0,
  WindowClose,
  WindowResize,
  KeyPressed,
  KeyReleased,
  MouseMoved,
  MouseButtonPressed,
  MouseButtonReleased,
  MouseScrolled
};

class Event {
public:
  bool Handled = false;
  virtual ~Event() = default;

  virtual EventType GetEventType() const = 0;
  virtual const char *GetName() const = 0;
  virtual std::string ToString() const { return GetName(); }
};

} // namespace Core
