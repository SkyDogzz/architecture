
#pragma once
#include "Core/Runtime/Events/Event.hpp"
#include <sstream>

namespace Core {

class KeyEvent : public Event {
public:
  int GetKeyCode() const { return m_KeyCode; }

protected:
  explicit KeyEvent(int keycode) : m_KeyCode(keycode) {}
  int m_KeyCode;
};

class KeyPressedEvent final : public KeyEvent {
public:
  KeyPressedEvent(int keycode, int repeatCount)
      : KeyEvent(keycode), m_RepeatCount(repeatCount) {}

  int GetRepeatCount() const { return m_RepeatCount; }

  EventType GetEventType() const override { return EventType::KeyPressed; }
  const char *GetName() const override { return "KeyPressedEvent"; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << GetName() << ": " << m_KeyCode << " (" << m_RepeatCount
       << " repeats)";
    return ss.str();
  }

private:
  int m_RepeatCount;
};

class KeyReleasedEvent final : public KeyEvent {
public:
  explicit KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}

  EventType GetEventType() const override { return EventType::KeyReleased; }
  const char *GetName() const override { return "KeyReleasedEvent"; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << GetName() << ": " << m_KeyCode;
    return ss.str();
  }
};

} // namespace Core
