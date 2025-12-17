
#pragma once
#include <memory>

struct GLFWwindow;

namespace Core {

class GraphicsContext {
public:
  virtual ~GraphicsContext() = default;
  virtual void Init() = 0;

  static std::unique_ptr<GraphicsContext> Create(GLFWwindow *window);
};

} // namespace Core
