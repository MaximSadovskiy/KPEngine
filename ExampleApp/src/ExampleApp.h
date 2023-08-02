#pragma once
#include "EntryPoint.h"

extern Kpe::Application* Kpe::CreateApplication();

class ExampleApp : public Kpe::Application
{
public:
	ExampleApp();
	ExampleApp(const int& width, const int& height, const bool& vSync = true);
	virtual ~ExampleApp();
	void OnUpdate(double& ts) override;
};
