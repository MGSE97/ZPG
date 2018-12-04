#include "MeshScene.h"
#include "BaseEngine.h"
#include "Assets.h"

void Application::Scenes::MeshScene::Load(Engine::BaseEngine* engine)
{
	Engine::Components::Graphics::Shader* shader = engine->Shaders->First();

	auto cube = new Engine::Components::Objects::Mesh();
	cube->Load(Assets::Meshes + "test.obj");
	for (auto& object : *cube->Components)
	{
		object->Material->SetShader(shader);
		object->Transform->Rotation(0, 90, 0);
	}

	Meshes->Add("cube", cube);
}

void Application::Scenes::MeshScene::Unload(Engine::BaseEngine* engine)
{
}
