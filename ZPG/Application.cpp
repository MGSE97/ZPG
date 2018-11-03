#include "Application.h"
#include <cstddef>
#include <cstdlib>
#include <cstdio>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

Application::Application::Application()
{
	Engines = new Generic::Dictionary<std::string, Engine::BaseEngine*>();
}

Application::Application::~Application()
{
	Engines->clear();
	delete Engines;
}

Application::Application* Application::Application::GetIntance()
{
	static Application instance;
	return &instance;
}

Application::Application* Application::Application::Init()
{
	RegisterEngines();
	return this;
}
