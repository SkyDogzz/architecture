
#include "Core/Runtime/Application.hpp"
#include <memory>

// factory
std::unique_ptr<Core::Layer> CreateSandboxLayer();

int main() {
  Core::WindowProps props;
  props.Title = "Sandbox 🖤";
  props.Width = 1280;
  props.Height = 720;
  props.VSync = true;

  Core::Application app(props);
  app.PushLayer(CreateSandboxLayer());
  app.Run();
  return 0;
}
