
#pragma once
#include "Core/Runtime/Events/Event.hpp"
#include <sstream>

namespace Core {

class MouseMovedEvent final : public Event {
public:
  MouseMovedEvent(double x, double y) : m_X(x), m_Y(y) {}
  double GetX() const { return m_X; }
  double GetY() const { return m_Y; }

  EventType GetEventType() const override { return EventType::MouseMoved; }
  const char *GetName() const override { return "MouseMovedEvent"; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << GetName() << ": " << m_X << ", " << m_Y;
    return ss.str();
  }

private:
  double m_X, m_Y;
};

class MouseScrolledEvent final : public Event {
public:
  MouseScrolledEvent(double xoff, double yoff)
      : m_XOffset(xoff), m_YOffset(yoff) {}
  EventType GetEventType() const override { return EventType::MouseScrolled; }
  const char *GetName() const override { return "MouseScrolledEvent"; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << GetName() << ": " << m_XOffset << ", " << m_YOffset;
    return ss.str();
  }

private:
  double m_XOffset, m_YOffset;
};

} // namespace Core
