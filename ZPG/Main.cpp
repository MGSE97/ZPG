//Include GLEW
#include <GL/glew.h>

//Include the standard C++ headers  
#include "Application.h"
#include <iostream>

int main(void)
{
	Application::Application::GetIntance()->Init()
		->Engines
		//->Get("basic")
		//->Get("camera")
		->Get("light")
		->Init(stdout)
		->Start();

	int v;
	std::cin >> v;
}