#pragma once

#include <memory>
#include "../WinWindow.h"

namespace Kpe {
	//should be singleton?
	class Renderer
	{
	public:
		Renderer(WinWindow* window);
		~Renderer();
		void BeginScene();
		void EndScene();
		void DrawSmh();
	private:
		void Init();
	private:
		WinWindow* m_window;
	};
}