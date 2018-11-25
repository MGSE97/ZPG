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
#include "StandartMaterial.h"
#include "Assets/Models/2/plain.h"

Application::Engines::LightEngine* Application::Engines::LightEngine::Init(std::FILE* errorStream)
{
	BaseEngine::Init(errorStream);

	angle = 0.0f;

	auto window = (new ::Engine::Components::Window(1024, 768, "ZPG - Camera", 100.0f))
		->Show()
		->Info(std::cout);
	Windows->Add("zpg", window);

	auto* shader = (new Engine::Components::Graphics::Shader())
		->Add("vertex", GL_VERTEX_SHADER, Assets::ShadersVertex + "Texture.glsl")
		->Add("fragment", GL_FRAGMENT_SHADER, Assets::ShadersFragment + "Volumetric.glsl");
		//->Add("fragment", GL_FRAGMENT_SHADER, Assets::ShadersFragment + "Texture.glsl");

	if (!shader->Compile())
		throw (-1);

	Shaders->Add("texture", shader);
	
	auto texture = new Engine::Components::Graphics::Texture(Assets::Models + "earth\\Albedo.jpg",  SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MULTIPLY_ALPHA | SOIL_FLAG_TEXTURE_REPEATS);

	Scenes->Add("triangle", new Scenes::TriangleScene());
	Scenes->Add("sphere", new Scenes::SphereScene());
	Scenes->Add("plane", new Scenes::PlaneScene());

	InputHandlers->Add(new Input::Handlers::LightingChangeInputHandler());
	InputHandlers->Add(new Input::Handlers::CameraInputHandler());

	SetActiveScene(Scenes->Get("sphere"));

	auto* lc = new Engine::Components::Graphics::LightConfiguration();
	lc->AmbientStrength = 0.f;
	lc->DiffuseStrength = 1.f;
	lc->SpecularStrength = 1.f;
	ActiveScene->Lights->Add("center", new Engine::Components::Light(shader, glm::vec3(0, 0, 0), glm::vec4(1), lc));
	auto* lc2 = new Engine::Components::Graphics::LightConfiguration();
	lc2->AmbientStrength = 0.f;
	lc2->DiffuseStrength = 3.0f;
	lc2->SpecularStrength = 6.0f;
	lc2->GlobalStrength = 0.3f;
	auto d = 3.f;
	ActiveScene->Lights->Add("rotatingX", new Engine::Components::Light(shader, glm::vec3(0, d, 0), glm::vec4(1, 0, 0, 1), lc2));
	ActiveScene->Lights->Add("rotatingY", new Engine::Components::Light(shader, glm::vec3(d, 0, 0), glm::vec4(0, 1, 0, 1), lc2));
	ActiveScene->Lights->Add("rotatingZ", new Engine::Components::Light(shader, glm::vec3(d, d, 0), glm::vec4(0, 0, 1, 1), lc2));

	ActiveScene->Lights->Add("rotatingXY", new Engine::Components::Light(shader, glm::vec3(0, 0, d), glm::vec4(1, 1, 0, 1), lc2));
	ActiveScene->Lights->Add("rotatingXZ", new Engine::Components::Light(shader, glm::vec3(0, d, 0), glm::vec4(1, 0, 1, 1), lc2));
	ActiveScene->Lights->Add("rotatingYZ", new Engine::Components::Light(shader, glm::vec3(d, 0, 0), glm::vec4(0, 1, 1, 1), lc2));

	ActiveScene->Cameras->Add("main", (new Engine::Components::Camera())
		//->SetPosition(new glm::vec3(2.5f, 2.5f, 2.f))
		->SetPosition(new glm::vec3(0.f, 0.f, -4.f))
		->SetDirection(new glm::vec3(0.f, 0.f, 0.f))
		->SetUp(new glm::vec3(0.f, 1.f, 0.f)));
	ActiveScene->Cameras->First()->Projection = new glm::mat4(glm::perspective(glm::radians(45.f), (float)window->Width / (float)window->Height, 0.1f, 100.0f));

	ActiveScene->BeginLoad(this);

	auto mat = new Materials::StandartMaterial(shader, glm::vec4(1.0f, 1.0f, 1.0f, 0.5f));
	auto pl = new Engine::Objects::Object(mat, plain, 6, 3, true, true);
	mat->Light.DiffuseStrength = 0.2f;
	mat->Light.SpecularSize = 64;
	pl->Transform->Position(0, -3, -3, true);
	pl->Transform->Rotation(90, 0, -60, true);
	pl->Transform->Rotation(0, 90, 0);
	pl->Transform->Scale(1, 2, 2, true);
	ActiveScene->Objects->Add("plain", pl);

	std::string lightPrefix = "light_";
	if (ActiveScene != nullptr && ActiveScene->Lights != nullptr && !ActiveScene->Lights->empty())
		for (auto& it : *ActiveScene->Lights)
			ActiveScene->Objects->Add(lightPrefix + it.first, it.second);

	if (ActiveScene != nullptr && ActiveScene->Objects != nullptr && !ActiveScene->Objects->empty())
		for (auto& it : *ActiveScene->Objects)
		{
			/*it.second->Material
				->Add(vertex, "viewMatrix", ActiveScene->ActiveCamera->Value)
				->Add(vertex, "projectionMatrix", ActiveScene->ActiveCamera->Projection)
				->Add(vertex, "cameraPos", ActiveScene->ActiveCamera->Position);*/
			//it.second->Material->Add("lightCount", new int(ActiveScene->Lights->size()));
			if (it.first.substr(0, lightPrefix.size()) != lightPrefix)
				it.second->Material->Add("material.hasTexture", new bool(true));
			else
				it.second->Material->Add("material.hasTexture", new bool(false));
			it.second->Transform->Rotation(-90, 0, 60);
			if (ActiveScene != nullptr && ActiveScene->Lights != nullptr && !ActiveScene->Lights->empty() && strncmp(it.first.c_str(), lightPrefix.c_str(), lightPrefix.size()) != 0)
			{
				int i = 0;
				for (auto& light : *ActiveScene->Lights)
				{
					light.second->Use(it.second->Material, i++);
				}
			}
		}
	return this;
}

void Application::Engines::LightEngine::Update(::Engine::Components::Window* window)
{
	//std::cout << "PS: " << specularSize << "\nSS: " << specularStrength << "\nDS: " << diffuseStrength << "\nAS: " << ambientStrength << "\nLP: " << ActiveScene->Lights->First()->Configuration.GlobalStrength << std::endl;

	if (ActiveScene != nullptr && ActiveScene->Lights != nullptr && !ActiveScene->Lights->empty())
	{
		float speed = 1.f;
		ActiveScene->Lights->Get("rotatingX")->Transform->RotateAround(glm::vec3(0, 0, 0), speed, glm::vec3(1, 0, 0));
		ActiveScene->Lights->Get("rotatingY")->Transform->RotateAround(glm::vec3(0, 0, 0), speed, glm::vec3(0, 1, 0));
		ActiveScene->Lights->Get("rotatingZ")->Transform->RotateAround(glm::vec3(0, 0, 0), speed, glm::vec3(0, 0, 1));
		ActiveScene->Lights->Get("rotatingXY")->Transform->RotateAround(glm::vec3(0, 0, 0), speed, glm::vec3(1, 1, 0));
		ActiveScene->Lights->Get("rotatingXZ")->Transform->RotateAround(glm::vec3(0, 0, 0), speed, glm::vec3(1, 0, 1));
		ActiveScene->Lights->Get("rotatingYZ")->Transform->RotateAround(glm::vec3(0, 0, 0), speed, glm::vec3(0, 1, 1));

		/*for (auto& it : *ActiveScene->Lights)
			it.second->Draw();*/
	}
	//return;
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
		}
			
	//angle += 0.1f;
}
