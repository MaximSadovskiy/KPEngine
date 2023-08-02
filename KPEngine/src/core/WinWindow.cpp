#include "KpePch.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Base.h"
#include "Application.h"
#include "WinWindow.h"
#include "render/OpenGLContext.h"

namespace Kpe {
	WinWindow::WinWindow(uint32_t width, uint32_t height, const char* title, bool isVsync)
		: m_windowWidth(width), m_windowHeight(height), m_windowTitle(title),
		m_isVsync(isVsync), m_isMinimized(0), m_isFocused(true)
	{
		SetUpContext();

		SetupCallbacks();

		Render();
	}
	void WinWindow::Render()
	{
		if (glewInit() != GLEW_OK) {
			KPE_LOG_INFO("Glew initialization error!");
			return;
		}
		uint32_t vert;
		float vertices[] =
		{
			-0.5f, -0.5f,
			 0.5f, -0.5f,
			 0.5f,  0.5f,
			 0.9f,  0.9f,
		};

		glGenBuffers(1, &vert);
		glBindBuffer(GL_ARRAY_BUFFER, vert);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

		uint32_t indexBuffer;
		uint32_t indices[] =
		{
			0, 1, 2,
			1, 2, 3,
		};
		glGenBuffers(1, &indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	}
	void WinWindow::OnUpdate(double& ts)
	{
		Loop(ts);

		glfwSwapBuffers(m_graphicWindow);
		glfwPollEvents();
	}
	inline void WinWindow::SetUpContext()
	{
		if (!glfwInit()) 
		{
			KPE_LOG_FATAL("Glfw initialization error!");
			return;
		}

		m_graphicWindow = glfwCreateWindow(m_windowWidth, m_windowHeight, m_windowTitle, nullptr, nullptr);
		KPE_ASSERT_DIST(!m_graphicWindow, KPE_LOG_FATAL("Failed to initialize Window"));

		glfwSwapInterval(m_isVsync);

		glfwMakeContextCurrent(m_graphicWindow);
		glfwSetWindowUserPointer(m_graphicWindow, this);
	}
	inline void WinWindow::SetSize(uint32_t width, uint32_t height)
	{
		m_windowWidth = width;
		m_windowHeight = height;

		glViewport(0, 0, m_windowWidth, m_windowHeight);

		m_isMinimized = (m_windowWidth == 0 || m_windowHeight == 0);
	}
	inline void WinWindow::Loop(double& ts)
	{
		if (m_isMinimized) return;

		KPE_LOG_TRACE("ts: {0}, fps: {1}.", ts, (int)(1 / ts));

		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.2f, 0.7f, 0.1f, 1.0f);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
	}
	inline void WinWindow::UpdateMousePos(double& xpos, double& ypos)
	{
		m_mouseXPos = xpos;
		m_mouseYPos = ypos;
	}
	inline void WinWindow::SetFocus(int& isFocused)
	{
		m_isFocused = isFocused;
	}
	inline int WinWindow::GetIsFocused()
	{
		return m_isFocused;
	}
	inline int WinWindow::GetIsMinimized()
	{
		return m_isMinimized;
	}
	inline void WinWindow::SetupCallbacks()
	{
		glfwSetErrorCallback([](int error_code, const char* description)
			{
				KPE_LOG_FATAL("Window glfw error: {0}, desc: {1}", error_code, description);
				Application::getInstance()->Shutdown();
			});
		glfwSetWindowSizeCallback(m_graphicWindow, [](GLFWwindow* window, int width, int height)
			{
				WinWindow* instance = (WinWindow*)glfwGetWindowUserPointer(window);
				if (!instance) return;
				KPE_LOG_DEGUB("Size event: width {0}, height {1}", width, height);
				instance->SetSize(width, height);
			});
		glfwSetWindowCloseCallback(m_graphicWindow, [](GLFWwindow* window)
			{
				WinWindow* instance = (WinWindow*)glfwGetWindowUserPointer(window);
				if (!instance) return;
				KPE_LOG_DEGUB("Shutting down window...");
				delete instance;
			});
		glfwSetCursorPosCallback(m_graphicWindow, [](GLFWwindow* window, double xpos, double ypos)
			{
				WinWindow* instance = (WinWindow*)glfwGetWindowUserPointer(window);
				if (!instance) return;
				if (!instance->GetIsFocused()) return;
				KPE_LOG_TRACE("Setting cursor pos x: {0}, y: {1}", xpos, ypos);
				instance->UpdateMousePos(xpos, ypos);
			});
		glfwSetKeyCallback(m_graphicWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WinWindow* instance = (WinWindow*)glfwGetWindowUserPointer(window);
				if (!instance) return;
				if (!instance->GetIsFocused()) return;
				KPE_LOG_TRACE("key {0}, scancode {1}, action {2}, mods {3}", key, scancode, action, mods);
			});
		glfwSetWindowFocusCallback(m_graphicWindow, [](GLFWwindow* window, int focused)
			{
				WinWindow* instance = (WinWindow*)glfwGetWindowUserPointer(window);
				if (!instance) return;
				instance->SetFocus(focused);
			});
	}
	WinWindow::~WinWindow()
	{
		glfwDestroyWindow(m_graphicWindow);
		//Temp
		Application::getInstance()->Shutdown();
	}
}
