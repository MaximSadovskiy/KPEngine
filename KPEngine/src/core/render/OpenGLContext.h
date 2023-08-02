#pragma once

class WinWindow;
struct GLFWwindow;
struct GLFWmonitor;

namespace Kpe {
	struct OpenGLContext
	{
	public:
		static bool SetUpContext();
		static void DestroyWindow(GLFWwindow* window);
		static void Terminate();
	};
}

