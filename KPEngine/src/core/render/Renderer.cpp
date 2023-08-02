#include "KpePch.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Renderer.h"
#include "OpenGLContext.h"
#include "../Base.h"

namespace Kpe {
	Renderer::Renderer(WinWindow* window)
		: m_window(window)
	{
		//Init();
	}
	void Renderer::Init()
	{
		/*if (OpenGLContext::SetUpContext())
		{
			KPE_LOG_FATAL("Failed to setup Render context");
			return;
		}*/

		//buffers..
		//textures...
		//shaders...
		//cameras...
	}
	Renderer::~Renderer()
	{
		OpenGLContext::Terminate();
	}
	void Renderer::BeginScene()
	{
	}
	void Renderer::EndScene()
	{
	}
	void Renderer::DrawSmh()
	{
	}
}