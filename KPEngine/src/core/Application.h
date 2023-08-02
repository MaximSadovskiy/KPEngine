#pragma once

#include "Base.h"

int main();

namespace Kpe 
{
	//Defenition
	class Logger;
	class WinWindow;
	class Renderer;
	class Event;

	class Application
	{
	public:
		Application();
		Application(const uint32_t width, const uint32_t height, const bool vSync = true);
		virtual ~Application();
		virtual void OnUpdate(double& ts);
		void Shutdown();
		static Application* getInstance();
	private:
		void Run();
		void OnEvent(Event& e);
		inline void Init();
	private:
		static Application* m_instance;
		Logger* m_logger;
		WinWindow* m_window;
		Renderer* m_render;
		uint32_t m_windowWidth, m_windowHeight;
		bool m_vSync;
		bool m_isRunning = true;
		int m_frameCount = 0;
		double m_frameTime = 0.0f;

		friend int ::main();
	};
}

