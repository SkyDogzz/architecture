
#pragma once
#include "Core/Platform/Window.hpp"
#include "Core/Runtime/Events/Event.hpp"
#include "Core/Runtime/LayerStack.hpp"
#include <memory>

namespace Core {

class Application {
public:
  explicit Application(const WindowProps &props = {});
  virtual ~Application() = default;

  void Run();
  void Close();

  void PushLayer(std::unique_ptr<Layer> layer);

  Window &GetWindow() { return *m_Window; }

private:
  void OnEvent(Event &e);

private:
  std::unique_ptr<Window> m_Window;
  LayerStack m_LayerStack;
  bool m_Running = true;
  double m_LastTime = 0.0;
};

} // namespace Core
