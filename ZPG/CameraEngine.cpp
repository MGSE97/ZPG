#include "CameraEngine.h"
#include "TriangleScene.h"
#include <iostream>
#include <glm/ext/matrix_clip_space.hpp> 
#include "SphereScene.h"
#include <windows.h>
#include "Assets.h"

Application::Engines::CameraEngine* Application::Engines::CameraEngine::Init(std::FILE* errorStream)
{
	BaseEngine::Init(errorStream);

	const char* vertex_shader =
		"#version 330\n"
		"layout(location=0) in vec3 vp;"
		"out vec3 ex_WorldPos;"
		"uniform mat4 modelMatrix;"
		"uniform mat4 viewMatrix;"
		"uniform mat4 projectionMatrix;"
		"void main () {"
		" gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4 (vp, 1.0);"
		"}";

	const char* fragment_shader =
		"#version 330\n"
		"uniform float color;"
		"out vec4 frag_colour;"
		"void main () {"
		"     frag_colour = vec4 (color, 1.0-color, 0.0, 1.0);"
		"}";

	M = glm::mat4(1.0f);
	angle = 0.0f;

	Windows->Add("zpg", (new ::Engine::Components::Window(800, 600, "ZPG - Camera", 100.0f))
		->Show()
		->Info(std::cout)
	);

	auto* vertex = new Engine::Components::Graphics::Shader(GL_VERTEX_SHADER, Assets::ShadersVertex + "Camera.glsl");
	Shaders->Add("vertex", vertex);
	Shaders->Add("fragment", new Engine::Components::Graphics::Shader(GL_FRAGMENT_SHADER, Assets::ShadersFragment + "Basic.glsl"));

	Programs->Add("basic", (new Engine::Components::Graphics::Program())->AddShaders(Shaders));

	Scenes->Add("triangle", new Scenes::TriangleScene());
	Scenes->Add("sphere", new Scenes::SphereScene());

	SetActiveScene(Scenes->Get("sphere"));

	ActiveScene->BeginLoad(this);

	ActiveScene->Cameras->Add("main", (new Engine::Components::Camera())
//		->SetPosition(new glm::vec3(2.5f, 2.5f, 2.f))
		->SetPosition(new glm::vec3(0.f, 1.5f, 4.f))
		->SetDirection(new glm::vec3(0.f, 0.f, 0.f))
		->SetUp(new glm::vec3(0.f, 0.f, 1.f)));

	ActiveScene->Objects->First()
		->Material->Values
		->Add(
			new Engine::Components::Graphics::MaterialValue<glm::mat4>(
				vertex,
				"viewMatrix",
				ActiveScene->Cameras->First()->Value)
		).Add(
			new Engine::Components::Graphics::MaterialValue<glm::mat4>(
				vertex,
				"projectionMatrix",
				new glm::mat4(glm::perspective(glm::radians(90.0f), 4.0f / 3.0f, 0.1f, 100.0f)))
		);
	return this;
}

void Application::Engines::CameraEngine::Update(::Engine::Components::Window* window)
{
	if (ActiveScene != nullptr && ActiveScene->Objects != nullptr && !ActiveScene->Objects->empty())
		for (auto& it : *ActiveScene->Objects)
		{
			//auto _fi = atan2(MouseY, MouseX);
			//auto _psi = atan2(MouseX, MouseY);
			//auto _fi = glm::radians(MouseX);
			//auto _psi = glm::radians(MouseY);
			auto _fi = (MouseX / window->Height);
			auto _psi =(MouseY / window->Width);

			std::cout << "FI:  " << _fi << "\nPSI: " << _psi << "\nObject: " << it.first << std::endl;

			ActiveScene->Cameras->First()->SetDirection(new glm::vec3(cos(_fi), sin(_fi), cos(_psi)));

			auto object = it.second;
			object->Draw();

			/*auto pm = glm::perspective(glm::radians(90.0f), 4.0f / 3.0f, 0.1f, 100.0f);
			auto c = ActiveScene->Cameras->First()->Value;
			Shaders->Get("vertex")->SendUniform(Programs->First(), "viewMatrix", c);
			Shaders->Get("vertex")->SendUniform(Programs->First(), "projectionMatrix", &pm);*/
			angle += 0.1f;
		}
}
