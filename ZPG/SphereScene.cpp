#include "SphereScene.h"
#include "BaseEngine.h"
#include <iostream>
#include <glm/ext/quaternion_transform.inl>
#include <glm/detail/type_quat.hpp>
#include "Sphere.h"
#include "Assets/Models/2/spheref.h"
#include "StandartMaterial.h"

Application::Scenes::SphereScene::SphereScene()
{
}

Application::Scenes::SphereScene::~SphereScene()
{
	Scene::~Scene();
}

void Application::Scenes::SphereScene::Load(Engine::BaseEngine* engine)
{
	// define material
	Engine::Components::Graphics::Shader* shader = engine->Shaders->First();

	// create object
	Objects->Add("sphere1", new ::Engine::Objects::Sphere(new Materials::StandartMaterial(shader, glm::vec4(1.0f, 1.0f, 0.0f, 0.5f)), sphere, 17280, 3));
	Objects->Add("sphere2", new ::Engine::Objects::Sphere(new Materials::StandartMaterial(shader, glm::vec4(1.0f, 0.0f, 1.0f, 0.5f)), sphere, 17280, 3));
	Objects->Add("sphere3", new ::Engine::Objects::Sphere(new Materials::StandartMaterial(shader, glm::vec4(0.0f, 1.0f, 1.0f, 0.5f)), sphere, 17280, 3));
	Objects->Add("sphere4", new ::Engine::Objects::Sphere(new Materials::StandartMaterial(shader, glm::vec4(1.0f, 1.0f, 1.0f, 0.5f)), sphere, 17280, 3));

	Objects->Get("sphere1")->Transform->Position(-2,  0, 0, true);
	Objects->Get("sphere2")->Transform->Position( 0,  2, 0, true);
	Objects->Get("sphere3")->Transform->Position( 2,  0, 0, true);
	Objects->Get("sphere4")->Transform->Position( 0, -2, 0, true);
	/*auto sphere = Objects->Get("sphere1");
	*(sphere->ModelMatrix) = glm::translate(*(sphere->ModelMatrix), glm::vec3(-2, 0, 0));

	sphere = Objects->Get("sphere2");
	*(sphere->ModelMatrix) = glm::translate(*(sphere->ModelMatrix), glm::vec3(0, 2, 0));

	sphere = Objects->Get("sphere3");
	*(sphere->ModelMatrix) = glm::translate(*(sphere->ModelMatrix), glm::vec3(2, 0, 0));

	sphere = Objects->Get("sphere4");
	*(sphere->ModelMatrix) = glm::translate(*(sphere->ModelMatrix), glm::vec3(0, -2, 0));*/
}

void Application::Scenes::SphereScene::FrameUpdate(Engine::BaseEngine* engine)
{
}

