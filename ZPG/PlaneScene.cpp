#include "PlaneScene.h"
#include "StandartMaterial.h"
#include "Assets/Models/2/plain.h"
#include "BaseEngine.h"

Application::Scenes::PlaneScene::PlaneScene()
{
}

Application::Scenes::PlaneScene::~PlaneScene()
{
}

void Application::Scenes::PlaneScene::Load(Engine::BaseEngine* engine)
{
	Engine::Components::Graphics::Shader* shader = engine->Shaders->First();

	// create object
	Objects->Add("plain", new ::Engine::Objects::Object(new Materials::StandartMaterial(shader, glm::vec4(1.0f, 1.0f, 0.0f, 0.5f)), plain, 32, 3));
}

void Application::Scenes::PlaneScene::Unload(Engine::BaseEngine* engine)
{
}
