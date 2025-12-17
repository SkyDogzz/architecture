#pragma once

namespace Core {

class RenderCommand {
public:
  static void SetClearColor(float r, float g, float b, float a);
  static void Clear();
  static void SetViewport(int x, int y, int w, int h);
};

} // namespace Core
