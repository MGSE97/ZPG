#include "Application.h"
#include <cstddef>
#include <cstdlib>
#include <cstdio>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

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
	std::cout << "Application.Init " << glfwGetTime() << " s\t> Registring Engines" << std::endl;
	RegisterEngines();
	std::cout << "Application.Init " << glfwGetTime() << " s\t> Registring Engines Complete" << std::endl;
	return this;
}
