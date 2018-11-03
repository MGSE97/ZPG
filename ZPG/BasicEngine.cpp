#include "BasicEngine.h"
#include "TriangleScene.h"
#include <iostream>
#include "SphereScene.h"
#include "Assets.h"


Application::Engines::BasicEngine* Application::Engines::BasicEngine::Init(std::FILE* errorStream)
{
	BaseEngine::Init(errorStream);

	const char* vertex_shader =
		"#version 330\n"
		"uniform mat4 modelMatrix;"
		"layout(location=0) in vec3 vp;"
		"layout(location=1) in vec3 vertNormal;"
		"void main () {"
		" gl_Position = modelMatrix * vec4 (vp, 1.0);"
		"}";

	const char*  fragment_shader =
		"#version 330\n"
		"uniform float color;"
		"out vec4 frag_colour;"
		"void main () {"
		"     frag_colour = vec4 (color, 1.0-color, 0.0, 1.0);"
		"}";

	Windows->Add("zpg", (new ::Engine::Components::Window(800, 600, "ZPG - Triangle", 100.0f))
		->Show()
		->Info(std::cout)
	);

	Shaders->Add("vertex", new Engine::Components::Graphics::Shader(GL_VERTEX_SHADER, vertex_shader));
	Shaders->Add("fragment", new Engine::Components::Graphics::Shader(GL_FRAGMENT_SHADER, fragment_shader));
	
	Shaders->Add("vertex", new Engine::Components::Graphics::Shader(GL_VERTEX_SHADER, Assets::ShadersVertex + "Basic.glsl"));
	Shaders->Add("fragment", new Engine::Components::Graphics::Shader(GL_FRAGMENT_SHADER, Assets::ShadersFragment + "Basic.glsl"));

	Programs->Add("basic", (new Engine::Components::Graphics::Program())->AddShaders(Shaders));

	Scenes->Add("triangle", new Scenes::TriangleScene());
	Scenes->Add("sphere", new Scenes::SphereScene());

	//SetActiveScene(Scenes->Get("triangle"));
	SetActiveScene(Scenes->Get("sphere"));

	M = glm::mat4(1.0f);
	angle = 0.0f;
	return this;
}

void Application::Engines::BasicEngine::Update(::Engine::Components::Window* window)
{
	if(ActiveScene != nullptr && ActiveScene->Objects != nullptr && !ActiveScene->Objects->empty())
	for (auto& it : *ActiveScene->Objects)
	{
		std::cout << "Object: " << it.first << std::endl;
		auto object = it.second;
		object->Draw();
		angle += 0.1f;
	}
}
