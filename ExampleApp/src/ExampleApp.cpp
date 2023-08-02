#include <iostream>
#include "ExampleApp.h"

using namespace Kpe;

ExampleApp::ExampleApp()
	: Application(400, 400, false)
{
}
ExampleApp::ExampleApp(const int& width, const int& height, const bool& vSync)
	: Application(width, height, vSync)
{

}

ExampleApp::~ExampleApp()
{
}

void ExampleApp::OnUpdate(double& ts)
{
}

extern Kpe::Application* Kpe::CreateApplication()
{
	return new ExampleApp();
};