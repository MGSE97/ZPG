#include "CameraInputHandler.h"
#include <glm/ext/matrix_transform.hpp>
//#define GLM_ENABLE_EXPERIMENTAL
//#include <glm/gtx/rotate_vector.hpp>
#include <iostream>
#include <windows.h>
#include "gmlExtensions.h"
#include "Sphere.h"
#include <array>
#include "BaseEngine.h"
#include "LigtEngine.h"
#include "Assets/Models/2/spheref.h"


Application::Input::Handlers::CameraInputHandler::CameraInputHandler()
{
	_lastMousePosition = glm::vec2(-1, -1);
	_yaw = 0.f;
	_pitch = 0.f;
}

Application::Input::Handlers::CameraInputHandler::~CameraInputHandler()
= default;

bool Application::Input::Handlers::CameraInputHandler::HandleKeys(Engine::BaseEngine* engine, Engine::Components::Window* window, Engine::Components::Scene* scene, Generic::Dictionary<short, bool>& keys, int keysActive)
{
	const float speed = 0.2f;
	glm::vec3 change = glm::vec3(0);

	if (keys['W'])
		 change -= *(scene->ActiveCamera->Front) * speed;
	if (keys['S'])
		change += *(scene->ActiveCamera->Front) * speed;
	if (keys['A'])
		change -= *(scene->ActiveCamera->Right) * speed;
	if (keys['D'])
		change += *(scene->ActiveCamera->Right) * speed;
	if (keys['E'])
		change -= *(scene->ActiveCamera->Up) * speed;
	if (keys['Q'])
		change += *(scene->ActiveCamera->Up) * speed;

	if (change != glm::vec3(0))
	{
		*(scene->ActiveCamera->Position) += change;
		*(scene->ActiveCamera->Direction) += change;
		scene->ActiveCamera->Update();
	}
	return true;
}
		

bool Application::Input::Handlers::CameraInputHandler::HandleMouse(Engine::BaseEngine* engine, Engine::Components::Window* window, Engine::Components::Scene* scene, double x, double y, Generic::Dictionary<short, bool>& keys, int keysActive)
{
	if (_lastMousePosition.x < 0)
	{
		_lastMousePosition.x = x;
		_lastMousePosition.y = y;
	}
	// Allow Move mouse without camera change
	if (keys[MK_R])
	{
		auto fow = glm::radians(90.f);
		const float sensitivity = 10.f;

		auto diff = glm::vec2(x, y) - _lastMousePosition;
		diff.x = diff.x * sensitivity * fow / static_cast<float>(window->Width);
		diff.y = diff.y * sensitivity * fow / static_cast<float>(window->Height);

		//fprintf(stderr, "Diff: %f, %f\t", diff.x, diff.y);

		if (diff.x != 0 || diff.y != 0)
		{
			*(scene->ActiveCamera->Direction) += *(scene->ActiveCamera->Right) * diff.x;
			*(scene->ActiveCamera->Direction) -= *(scene->ActiveCamera->Up) * diff.y;
			scene->ActiveCamera->Update();
		}
	}

	// Draw look point
	/*auto name = "target";
	auto obj = scene->Objects->Get(name);
	if (obj == nullptr)
	{

		auto mat = new Materials::StandartMaterial(engine->Shaders->First());
		mat->Add("material.color", new glm::vec4(255.f, 0.f, 0.f, 1.f));
		mat->Add("material.lightConfiguration.useLighting", new bool(false));
		obj = new Engine::Components::Objects::Object(mat, sphere, 2880, 3, true);
		obj->Transform->Position(*scene->ActiveCamera->Direction, true);
		obj->Transform->Scale(0.1f, true);
		//*(object->ModelMatrix) = glm::scale(glm::translate(glm::mat4(1.f), *scene->ActiveCamera->Direction), glm::vec3(0.1f, 0.1f, 0.1f));
		scene->Objects->Add(name, obj);
	}
	else
	{
		obj->Transform->Position(*scene->ActiveCamera->Direction, true);
		//*(obj->ModelMatrix) = glm::scale(glm::translate(glm::mat4(1.f), *scene->ActiveCamera->Direction), glm::vec3(0.1f, 0.1f, 0.1f));
	}*/

	_lastMousePosition.x = x;
	_lastMousePosition.y = y;
	return true;
}
