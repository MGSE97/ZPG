#include "Application.h"
#include "BasicEngine.h"
#include "CameraEngine.h"
#include <iostream>
#include "LigtEngine.h"

void Application::Application::RegisterEngines()
{
	Engines->
		 Add("basic", new Engines::BasicEngine())
		.Add("camera", new Engines::CameraEngine())
		.Add("light", new Engines::LightEngine())
	;
}
