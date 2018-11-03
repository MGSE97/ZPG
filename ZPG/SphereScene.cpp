#include "SphereScene.h"
#include "BaseEngine.h"
#include <iostream>
#include <glm/ext/quaternion_transform.inl>
#include <glm/detail/type_quat.hpp>
#include "Sphere.h"
#include "Assets/Models/2/spheref.h"

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
	Engine::Components::Graphics::Program* program = engine->Programs->Get("basic");

	// create object
	Objects->Add("sphere1", new ::Engine::Objects::Sphere(new Engine::Components::Graphics::Material(program), sphere, 17280, 3));
	Objects->Add("sphere2", new ::Engine::Objects::Sphere(new Engine::Components::Graphics::Material(program), sphere, 17280, 3));
	Objects->Add("sphere3", new ::Engine::Objects::Sphere(new Engine::Components::Graphics::Material(program), sphere, 17280, 3));
	Objects->Add("sphere4", new ::Engine::Objects::Sphere(new Engine::Components::Graphics::Material(program), sphere, 17280, 3));
	
	auto sphere = Objects->Get("sphere1");
	sphere->Material->Values
		->Add(
			new Engine::Components::Graphics::MaterialValue<glm::vec4>(
				program->Shaders->Get("fragment"), "color", new glm::vec4(1.0f, 1.0f, 0.0f, 0.5f))
		);
	*(sphere->ModelMatrix) = glm::translate(*(sphere->ModelMatrix), glm::vec3(-2, 0, 0));

	sphere = Objects->Get("sphere2");
	sphere->Material->Values
		->Add(
			new Engine::Components::Graphics::MaterialValue<glm::vec4>(
				program->Shaders->Get("fragment"), "color", new glm::vec4(1.0f, 0.0f, 1.0f, 0.5f))
		);
	*(sphere->ModelMatrix) = glm::translate(*(sphere->ModelMatrix), glm::vec3(0, 2, 0));

	sphere = Objects->Get("sphere3");
	sphere->Material->Values
		->Add(
			new Engine::Components::Graphics::MaterialValue<glm::vec4>(
				program->Shaders->Get("fragment"), "color", new glm::vec4(0.0f, 1.0f, 1.0f, 0.5f))
		);
	*(sphere->ModelMatrix) = glm::translate(*(sphere->ModelMatrix), glm::vec3(2, 0, 0));

	sphere = Objects->Get("sphere4");
	sphere->Material->Values
		->Add(
			new Engine::Components::Graphics::MaterialValue<glm::vec4>(
				program->Shaders->Get("fragment"), "color", new glm::vec4(1.0f, 1.0f, 1.0f, 0.5f))
		);
	*(sphere->ModelMatrix) = glm::translate(*(sphere->ModelMatrix), glm::vec3(0, -2, 0));
}

void Application::Scenes::SphereScene::FrameUpdate(Engine::BaseEngine* engine)
{
}

