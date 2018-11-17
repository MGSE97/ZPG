#include "LigtEngine.h"
#include "TriangleScene.h"
#include <iostream>
#include <glm/ext/matrix_clip_space.hpp> 
#include "SphereScene.h"
#include <windows.h>
#include "CameraInputHandler.h"
#include "Assets.h"
#include "LightingChangeInputHandler.h"
#include "Texture.h"
#include "PlaneScene.h"

Application::Engines::LightEngine* Application::Engines::LightEngine::Init(std::FILE* errorStream)
{
	BaseEngine::Init(errorStream);

	angle = 0.0f;

	auto window = (new ::Engine::Components::Window(1024, 768, "ZPG - Camera", 100.0f))
		->Show()
		->Info(std::cout);
	Windows->Add("zpg", window);

	auto* shader = (new Engine::Components::Graphics::Shader())
		->Add("vertex", GL_VERTEX_SHADER, Assets::ShadersVertex + "Light.glsl")
		->Add("fragment", GL_FRAGMENT_SHADER, Assets::ShadersFragment + "Light.glsl");

	if (!shader->Compile())
		throw (-1);

	Shaders->Add("light", shader);
	
	auto texture = new Engine::Components::Graphics::Texture(Assets::Textures + "blabla.png");

	/*auto* vertex = new Engine::Components::Graphics::Shader(GL_VERTEX_SHADER, Assets::ShadersVertex + "Light.glsl");
	auto* fragment = new Engine::Components::Graphics::Shader(GL_FRAGMENT_SHADER, Assets::ShadersFragment + "Light.glsl");*/

	auto* vertex = new Engine::Components::Graphics::Shader(GL_VERTEX_SHADER, Assets::ShadersVertex + "Texture.glsl");
	auto* fragment = new Engine::Components::Graphics::Shader(GL_FRAGMENT_SHADER, Assets::ShadersFragment + "Texture.glsl");
	Shaders->Add("vertex", vertex);
	Shaders->Add("fragment", fragment);

	//Programs->Add("basic", (new Engine::Components::Graphics::Program())->AddShaders(Shaders));

	Scenes->Add("triangle", new Scenes::TriangleScene());
	Scenes->Add("sphere", new Scenes::SphereScene());
	Scenes->Add("plane", new Scenes::PlaneScene());

	InputHandlers->Add(new Input::Handlers::LightingChangeInputHandler());
	InputHandlers->Add(new Input::Handlers::CameraInputHandler());

	SetActiveScene(Scenes->Get("sphere"));

	auto* lc = new Engine::Components::Graphics::LightConfiguration();
	lc->AmbientStrength = 1.f;
	lc->DiffuseStrength = 1.f;
	lc->SpecularStrength = 1.f;
	ActiveScene->Lights->Add("light" , new Engine::Components::Light(shader, glm::vec3(0, 0, 0), glm::vec4(1), lc));

	ActiveScene->Cameras->Add("main", (new Engine::Components::Camera())
		//->SetPosition(new glm::vec3(2.5f, 2.5f, 2.f))
		->SetPosition(new glm::vec3(0.f, 0.f, -4.f))
		->SetDirection(new glm::vec3(0.f, 0.f, 0.f))
		->SetUp(new glm::vec3(0.f, 1.f, 0.f)));
	ActiveScene->Cameras->First()->Projection = new glm::mat4(glm::perspective(glm::radians(45.f), (float)window->Width / (float)window->Height, 0.1f, 100.0f));

	ActiveScene->BeginLoad(this);
	std::string lightPrefix = "light_";
	if (ActiveScene != nullptr && ActiveScene->Lights != nullptr && !ActiveScene->Lights->empty())
		for (auto& it : *ActiveScene->Lights)
		{
			ActiveScene->Objects->Add(lightPrefix + it.first, it.second);
		}
	if (ActiveScene != nullptr && ActiveScene->Objects != nullptr && !ActiveScene->Objects->empty())
		for (auto& it : *ActiveScene->Objects)
		{
			/*it.second->Material
				->Add(vertex, "viewMatrix", ActiveScene->ActiveCamera->Value)
				->Add(vertex, "projectionMatrix", ActiveScene->ActiveCamera->Projection)
				->Add(vertex, "cameraPos", ActiveScene->ActiveCamera->Position);*/
			texture->Use(Programs->Get("basic"), fragment, "model.base");
			if (ActiveScene != nullptr && ActiveScene->Lights != nullptr && !ActiveScene->Lights->empty() && 
				strncmp(it.first.c_str(), lightPrefix.c_str(), lightPrefix.size()) != 0)
				for (auto& light : *ActiveScene->Lights)
				{
					light.second->Use(it.second->Material);
				}
		}
	return this;
}

void Application::Engines::LightEngine::Update(::Engine::Components::Window* window)
{
	//std::cout << "PS: " << specularSize << "\nSS: " << specularStrength << "\nDS: " << diffuseStrength << "\nAS: " << ambientStrength << "\nLP: " << ActiveScene->Lights->First()->Configuration.GlobalStrength << std::endl;
	
	if (ActiveScene != nullptr && ActiveScene->Objects != nullptr && !ActiveScene->Objects->empty())
		for (auto& it : *ActiveScene->Objects)
		{
			/*auto _fi = glm::radians(90.f*(MouseX / window->Height));
			auto _psi = glm::radians(90.f*(MouseY / window->Width));

			std::cout << "FI:  " << _fi << "\nPSI: " << _psi << "\nObject: " << it.first << std::endl;
			*/
			//ActiveScene->Cameras->First()->SetDirection(new glm::vec3(cos(_fi), sin(_fi), cos(_psi)));
			//std::cout << "Object: " << it.first << (it.second->Clicked?" (CLICKED)":"                ") << std::endl;
			auto object = it.second;
			object->Draw();
			
			angle += 0.1f;
		}
}
