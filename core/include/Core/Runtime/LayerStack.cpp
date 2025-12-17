
// LayerStack.cpp
#include "Core/Runtime/LayerStack.hpp"

namespace Core {

LayerStack::~LayerStack() {
  for (auto &layer : m_Layers)
    layer->OnDetach();
}

void LayerStack::PushLayer(std::unique_ptr<Layer> layer) {
  layer->OnAttach();
  m_Layers.emplace_back(std::move(layer));
}

} // namespace Core
