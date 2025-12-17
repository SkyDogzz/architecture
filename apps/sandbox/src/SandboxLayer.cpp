
#include "Core/Foundation/Log.hpp"
#include "Core/Graphics/RenderCommand.hpp"
#include "Core/Runtime/Events/KeyEvents.hpp"
#include "Core/Runtime/Layer.hpp"

#include <memory>

class SandboxLayer final : public Core::Layer {
public:
  SandboxLayer() : Layer("SandboxLayer") {}

  void OnAttach() override {
    Core::Log(Core::LogLevel::Info, "SandboxLayer attached 😳🖤");
  }

  void OnUpdate(float) override {}

  void OnRender() override {
    Core::RenderCommand::SetClearColor(0.08f, 0.05f, 0.10f, 1.0f);
    Core::RenderCommand::Clear();
  }

  void OnEvent(Core::Event &e) override {
    if (e.GetEventType() == Core::EventType::KeyPressed) {
      auto &ke = static_cast<Core::KeyPressedEvent &>(e);
      if (ke.GetKeyCode() == /* ESC */ 256) { // GLFW_KEY_ESCAPE
        Core::Log(Core::LogLevel::Info, "ESC pressed (event seen) 🕯️");
      }
    }
  }
};

std::unique_ptr<Core::Layer> CreateSandboxLayer() {
  return std::make_unique<SandboxLayer>();
}
