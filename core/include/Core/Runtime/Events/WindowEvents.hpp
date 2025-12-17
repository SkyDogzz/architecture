
#pragma once
#include "Core/Runtime/Events/Event.hpp"
#include <sstream>

namespace Core {

class WindowResizeEvent final : public Event {
public:
  WindowResizeEvent(int w, int h) : m_Width(w), m_Height(h) {}

  int GetWidth() const { return m_Width; }
  int GetHeight() const { return m_Height; }

  EventType GetEventType() const override { return EventType::WindowResize; }
  const char *GetName() const override { return "WindowResizeEvent"; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << GetName() << ": " << m_Width << "x" << m_Height;
    return ss.str();
  }

private:
  int m_Width, m_Height;
};

class WindowCloseEvent final : public Event {
public:
  EventType GetEventType() const override { return EventType::WindowClose; }
  const char *GetName() const override { return "WindowCloseEvent"; }
};

} // namespace Core
