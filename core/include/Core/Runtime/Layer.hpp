
#pragma once
#include "Core/Runtime/Events/Event.hpp"
#include <string>

namespace Core {

class Layer {
public:
  explicit Layer(std::string name = "Layer") : m_Name(std::move(name)) {}
  virtual ~Layer() = default;

  virtual void OnAttach() {}
  virtual void OnDetach() {}
  virtual void OnUpdate(float dt) { (void)dt; }
  virtual void OnRender() {}
  virtual void OnEvent(Event &e) { (void)e; }

  const std::string &GetName() const { return m_Name; }

private:
  std::string m_Name;
};

} // namespace Core
