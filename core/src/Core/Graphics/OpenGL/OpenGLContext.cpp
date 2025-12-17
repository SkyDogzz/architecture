
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Core/Foundation/Assert.hpp"
#include "Core/Foundation/Log.hpp"
#include "Core/Graphics/GraphicsContext.hpp"

namespace Core {

class OpenGLContext final : public GraphicsContext {
public:
	explicit OpenGLContext(GLFWwindow* window) : m_Window(window) {
		CORE_ASSERT(window, "OpenGLContext: window is null");
	}

	void Init() override {
		glfwMakeContextCurrent(m_Window);

		CORE_ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize GLAD");

		Log(LogLevel::Info, std::string("OpenGL Vendor: ") + (const char*)glGetString(GL_VENDOR));
		Log(LogLevel::Info, std::string("OpenGL Renderer: ") + (const char*)glGetString(GL_RENDERER));
		Log(LogLevel::Info, std::string("OpenGL Version: ") + (const char*)glGetString(GL_VERSION));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

private:
	GLFWwindow* m_Window;
};

std::unique_ptr<GraphicsContext> GraphicsContext::Create(GLFWwindow* window) {
	return std::make_unique<OpenGLContext>(window);
}

}  // namespace Core
