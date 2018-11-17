#include "TriangleScene.h"
#include "BaseEngine.h"
#include <iostream>
#include <glm/ext/quaternion_transform.inl>
#include <glm/detail/type_quat.hpp>

Application::Scenes::TriangleScene::TriangleScene()
{
	modelMatrix = new glm::mat4(1.0f);
	angle = new float(0.0f);
	color = new float(0.0f);
}

Application::Scenes::TriangleScene::~TriangleScene()
{
	delete modelMatrix;
	delete angle;
	Scene::~Scene();
}

void Application::Scenes::TriangleScene::Load(Engine::BaseEngine* engine)
{
	delete modelMatrix;
	delete angle;
	modelMatrix = new glm::mat4(1.0f);
	angle = new float(1.0f);

	// define mesh
	float points[] = {
		0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};
	float* p = points;

	// define material
	auto material = new Engine::Components::Graphics::Material(engine->Shaders->First());
	material->Add("color", new glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	// create object
	Objects->Add("triangle", new ::Engine::Objects::Object(material, p, 9));
}

void Application::Scenes::TriangleScene::FrameUpdate(Engine::BaseEngine* engine)
{
	*angle += 0.1f;
	*color = *angle - static_cast<long>(*angle);
}
