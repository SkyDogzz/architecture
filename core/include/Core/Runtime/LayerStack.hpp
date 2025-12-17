
// LayerStack.hpp
#pragma once
#include "Core/Runtime/Layer.hpp"
#include <memory>
#include <vector>

namespace Core {

class LayerStack {
public:
  LayerStack() = default;
  ~LayerStack();

  void PushLayer(std::unique_ptr<Layer> layer);

  auto begin() { return m_Layers.begin(); }
  auto end() { return m_Layers.end(); }

private:
  std::vector<std::unique_ptr<Layer>> m_Layers;
};

} // namespace Core
