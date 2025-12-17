
#include "Core/Runtime/Application.hpp"
#include "Core/Foundation/Log.hpp"
#include "Core/Graphics/RenderCommand.hpp"
#include "Core/Runtime/Events/WindowEvents.hpp"

#include <GLFW/glfw3.h> // for glfwGetTime only

namespace Core {

Application::Application(const WindowProps &props) {
  m_Window = Window::Create(props);
  m_Window->SetEventCallback([this](Event &e) { OnEvent(e); });

  m_LastTime = glfwGetTime();
}

void Application::PushLayer(std::unique_ptr<Layer> layer) {
  m_LayerStack.PushLayer(std::move(layer));
}

void Application::Close() { m_Running = false; }

void Application::OnEvent(Event &e) {
  // Core-level handling
  if (e.GetEventType() == EventType::WindowClose) {
    Close();
    e.Handled = true;
  }
  if (e.GetEventType() == EventType::WindowResize) {
    auto &re = static_cast<WindowResizeEvent &>(e);
    RenderCommand::SetViewport(0, 0, re.GetWidth(), re.GetHeight());
  }

  // Propagate to layers (top-most first)
  for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
    --it;
    (*it)->OnEvent(e);
    if (e.Handled)
      break;
  }
}

void Application::Run() {
  Log(LogLevel::Info, "Application running 🖤");

  while (m_Running) {
    double now = glfwGetTime();
    float dt = static_cast<float>(now - m_LastTime);
    m_LastTime = now;

    for (auto &layer : m_LayerStack)
      layer->OnUpdate(dt);

    for (auto &layer : m_LayerStack)
      layer->OnRender();

    m_Window->OnUpdate();
  }

  Log(LogLevel::Info, "Application shutdown 💀");
}

} // namespace Core
