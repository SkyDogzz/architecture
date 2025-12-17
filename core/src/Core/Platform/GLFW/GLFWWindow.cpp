
#include "Core/Foundation/Assert.hpp"
#include "Core/Foundation/Log.hpp"
#include "Core/Platform/Window.hpp"

#include "Core/Runtime/Events/KeyEvents.hpp"
#include "Core/Runtime/Events/MouseEvents.hpp"
#include "Core/Runtime/Events/WindowEvents.hpp"

#include "Core/Graphics/GraphicsContext.hpp"

#include <GLFW/glfw3.h>
#include <memory>

namespace Core {

struct GLFWWindowData {
  WindowProps Props;
  Window::EventCallbackFn EventCallback;
  bool VSync = true;
};

class GLFWWindow final : public Window {
public:
  explicit GLFWWindow(const WindowProps &props) { Init(props); }
  ~GLFWWindow() override { Shutdown(); }

  void OnUpdate() override {
    glfwPollEvents();
    glfwSwapBuffers(m_Window);
  }

  int GetWidth() const override { return m_Data.Props.Width; }
  int GetHeight() const override { return m_Data.Props.Height; }

  void SetEventCallback(const EventCallbackFn &cb) override {
    m_Data.EventCallback = cb;
  }

  void SetVSync(bool enabled) override {
    glfwSwapInterval(enabled ? 1 : 0);
    m_Data.VSync = enabled;
  }

  bool IsVSync() const override { return m_Data.VSync; }

  void *GetNativeHandle() const override { return m_Window; }

private:
  void Init(const WindowProps &props) {
    m_Data.Props = props;

    static bool glfwInitialized = false;
    if (!glfwInitialized) {
      CORE_ASSERT(glfwInit(), "Failed to init GLFW");
      glfwInitialized = true;
      Log(LogLevel::Info, "GLFW initialized");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    m_Window = glfwCreateWindow(props.Width, props.Height, props.Title.c_str(),
                                nullptr, nullptr);
    CORE_ASSERT(m_Window, "Failed to create GLFW window");

    m_Context = GraphicsContext::Create(m_Window);
    m_Context->Init();

    glfwSetWindowUserPointer(m_Window, &m_Data);
    SetVSync(props.VSync);

    // --- Callbacks -> Core Events ---
    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow *w, int width,
                                           int height) {
      auto &data = *static_cast<GLFWWindowData *>(glfwGetWindowUserPointer(w));
      data.Props.Width = width;
      data.Props.Height = height;
      WindowResizeEvent e(width, height);
      data.EventCallback(e);
    });

    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *w) {
      auto &data = *static_cast<GLFWWindowData *>(glfwGetWindowUserPointer(w));
      WindowCloseEvent e;
      data.EventCallback(e);
    });

    glfwSetKeyCallback(m_Window, [](GLFWwindow *w, int key, int, int action,
                                    int) {
      auto &data = *static_cast<GLFWWindowData *>(glfwGetWindowUserPointer(w));
      if (action == GLFW_PRESS) {
        KeyPressedEvent e(key, 0);
        data.EventCallback(e);
      } else if (action == GLFW_RELEASE) {
        KeyReleasedEvent e(key);
        data.EventCallback(e);
      } else if (action == GLFW_REPEAT) {
        KeyPressedEvent e(key, 1);
        data.EventCallback(e);
      }
    });

    glfwSetCursorPosCallback(m_Window, [](GLFWwindow *w, double x, double y) {
      auto &data = *static_cast<GLFWWindowData *>(glfwGetWindowUserPointer(w));
      MouseMovedEvent e(x, y);
      data.EventCallback(e);
    });

    glfwSetScrollCallback(m_Window, [](GLFWwindow *w, double xoff,
                                       double yoff) {
      auto &data = *static_cast<GLFWWindowData *>(glfwGetWindowUserPointer(w));
      MouseScrolledEvent e(xoff, yoff);
      data.EventCallback(e);
    });

    Log(LogLevel::Info, "Window created");
  }

  void Shutdown() {
    m_Context.reset();
    if (m_Window) {
      glfwDestroyWindow(m_Window);
      m_Window = nullptr;
    }
  }

private:
  GLFWwindow *m_Window = nullptr;
  GLFWWindowData m_Data{};
  std::unique_ptr<GraphicsContext> m_Context;
};

std::unique_ptr<Window> Window::Create(const WindowProps &props) {
  return std::make_unique<GLFWWindow>(props);
}

} // namespace Core
