
#include "Core/Graphics/RenderCommand.hpp"
#include <glad/glad.h>

namespace Core {

void RenderCommand::SetClearColor(float r, float g, float b, float a) {
  glClearColor(r, g, b, a);
}

void RenderCommand::Clear() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderCommand::SetViewport(int x, int y, int w, int h) {
  glViewport(x, y, w, h);
}

} // namespace Core
