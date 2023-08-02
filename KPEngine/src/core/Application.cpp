#include "KpePch.h"

//todo
//#include "imgui/imgui.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Base.h"
#include "Application.h"
#include "events/Event.h"
#include "Events/WindowEvent.h"
#include "render/Renderer.h"
#include "WinWindow.h"

namespace Kpe
{
	inline Application* Application::m_instance = nullptr;

	Application::Application()
		: m_windowWidth(400), m_windowHeight(400), m_vSync(true)
	{
		Init();
	}
	Application::Application(const uint32_t width, const uint32_t height, const bool vSync)
		: m_windowWidth(width), m_windowHeight(height), m_vSync(vSync)
	{
		Init();
	}
	void Application::Run()
	{
		KPE_ASSERT_DEBUG(!m_window, KPE_DEBUGBREAK());

		while (m_isRunning)
		{
			double time = glfwGetTime();
			double temp = time;
			time -= m_frameTime;
			m_frameTime = temp;

			//Client defined
			OnUpdate(time);

			m_window->OnUpdate(time);
		}
	}
	inline void Application::Init()
	{
		m_instance = this;
		m_logger = KPE_GET_LOGGER();
		m_window = new WinWindow(m_windowWidth, m_windowHeight);
		m_render = new Renderer(m_window);
	}
	void Application::OnEvent(Event& e) 
	{
		//todo
		/*Event::Dispatch<WindowCloseEvent>(e);
		Event::Dispatch<WindowResizeEvent>(e);*/
	}
	Kpe::Application* Application::getInstance()
	{
		return m_instance;
	}
	void Application::Shutdown()
	{
		KPE_LOG_DEGUB("Shutting down application...");
		WindowCloseEvent e;
		OnEvent(e);
		m_isRunning = false;
	}
	void Application::OnUpdate(double& ts)
	{
	}
	Application::~Application()
	{
		delete m_logger;
		glfwTerminate();
	}
}
