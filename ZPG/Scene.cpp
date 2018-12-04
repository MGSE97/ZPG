#include "Scene.h"
#include <iostream>
#include "Light.h"

Engine::Components::Scene::Scene()
{
	Objects = new Generic::Dictionary<std::string, Engine::Objects::Object*>();
	Meshes = new Generic::Dictionary<std::basic_string<char>, Objects::Mesh*>();
	Cameras = new Generic::Dictionary<std::string, Camera*>();
	Lights = new Generic::Dictionary<std::string, Light*>();
	Loaded = false;
	ActiveCamera = nullptr;
}


Engine::Components::Scene::~Scene()
{
	Objects->clear();
	delete Objects;
	Cameras->clear();
	delete Cameras;
	Lights->clear();
	delete Lights;
}

void Engine::Components::Scene::Load(BaseEngine* engine)
{
}

void Engine::Components::Scene::Unload(BaseEngine* engine)
{
	for (auto& Object : *Objects)
		delete Object.second;
	Objects->clear();
	Loaded = false;
}

void Engine::Components::Scene::BeginLoad(BaseEngine* engine)
{
	if (!Loaded)
	{
		Load(engine);
		if (ActiveCamera == nullptr)
			SetActiveCamera();
		Loaded = true;
	}
}

void Engine::Components::Scene::FrameUpdate(BaseEngine* engine)
{
}

void Engine::Components::Scene::SetActiveCamera(Camera* camera)
{
	if (camera == nullptr)
		ActiveCamera = Cameras->First();
	else
		ActiveCamera = camera;
	if(ActiveCamera != nullptr)
		ActiveCamera->Update();
}
