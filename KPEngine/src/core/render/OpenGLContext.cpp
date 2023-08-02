#include "KpePch.h"
#include "Base.h"
#include "OpenGLContext.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "WinWindow.h"

namespace Kpe {
	bool OpenGLContext::SetUpContext()
	{
		if (glewInit() != GL_TRUE)
		{
			KPE_LOG_FATAL("Glew initialization error!");
			return false;
		}
		if (!glfwInit())
		{
			KPE_LOG_FATAL("Glfw initialization error!");
			return false;
		}
		return true;
	}
	void OpenGLContext::DestroyWindow(GLFWwindow* window)
	{
		glfwDestroyWindow(window);
	}
	void OpenGLContext::Terminate()
	{
		glfwTerminate();
	}
}