#pragma once

struct GLFWwindow;
namespace Kpe {
	class WinWindow
	{
	public:
		WinWindow(uint32_t width, uint32_t height, const char* title = "MainWindow", bool isVsync = true);
		~WinWindow();
		void OnUpdate(double& ts);
		inline void SetSize(uint32_t width, uint32_t height);
		inline void SetFocus(int& isFocused);
	private:
		inline void Loop(double& ts);
		inline void UpdateMousePos(double& xpos, double& ypos);
		void Render();
		inline void SetUpContext();
		inline void SetupCallbacks();
		inline int GetIsFocused();
		inline int GetIsMinimized();
	private:
		GLFWwindow* m_graphicWindow;
		const char* m_windowTitle;
		uint32_t m_windowHeight;
		uint32_t m_windowWidth;
		int m_isFocused;
		int m_isMinimized = false;
		double m_mouseXPos = 0;
		double m_mouseYPos = 0;
		bool m_isVsync;
		bool m_isRunning = true;
	};
}