#pragma once
#include "core/Application.h"

namespace Kpe 
{
	extern Application* CreateApplication();
}
int main()
{
	Kpe::Application* app = Kpe::CreateApplication();

	app->Run();

	delete app;
	return 0;
}