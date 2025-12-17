
#pragma once
#include "Core/Runtime/Events/Event.hpp"
#include <functional>
#include <string>

namespace Core {

struct WindowProps {
  std::string Title = "Core Window";
  int Width = 1280;
  int Height = 720;
  bool VSync = true;
};

class Window {
public:
  using EventCallbackFn = std::function<void(Event &)>;

  virtual ~Window() = default;

  virtual void OnUpdate() = 0;
  virtual int GetWidth() const = 0;
  virtual int GetHeight() const = 0;

  virtual void SetEventCallback(const EventCallbackFn &cb) = 0;
  virtual void SetVSync(bool enabled) = 0;
  virtual bool IsVSync() const = 0;

  virtual void *GetNativeHandle() const = 0;

  static std::unique_ptr<Window> Create(const WindowProps &props);
};

} // namespace Core
