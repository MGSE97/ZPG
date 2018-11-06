#include "LightingChangeInputHandler.h"
#include <glm/ext/matrix_transform.hpp>
#include "LigtEngine.h"
#include "StandartMaterial.h"

bool Application::Input::Handlers::LightingChangeInputHandler::HandleKeys(Engine::BaseEngine* engine, Engine::Components::Window* window, Engine::Components::Scene* scene, Generic::Dictionary<short, bool>& keys, int keysActive)
{
	if(keys['L'] && dynamic_cast<Application::Engines::LightEngine*>(engine) != nullptr)
	{
		if (_selectedLight == nullptr)
			_selectedLight = scene->Lights->First();
		auto lightEngine = dynamic_cast<Application::Engines::LightEngine*>(engine);

		const auto increment = (keys['R'] ? 1 : (keys['F'] ? -1 : 0));


		if (scene != nullptr && scene->Objects != nullptr && !scene->Objects->empty())
			for (auto& it : *scene->Objects)
			{
				auto* material = dynamic_cast<Materials::StandartMaterial*>(it.second->Material);
				if(material == nullptr)
					continue;

				auto* mlc = &material->Light;
				if (keys['V'])
					mlc->SpecularSize += increment;
				if (keys['C'])
					mlc->SpecularStrength += increment * .005f;
				if (keys['X'])
					mlc->DiffuseStrength += increment * .005f;
				if (keys['Z'])
					mlc->AmbientStrength += increment * .001f;

				if (keys['N'])
				{
					mlc->SpecularStrength = 0.f;
					mlc->DiffuseStrength = 0.f;
					mlc->AmbientStrength = 0.f;
				}
				if (keys['M'])
				{
					mlc->SpecularStrength = 0.5f;
					mlc->DiffuseStrength = 0.5f;
					mlc->AmbientStrength = 0.2f;
				}
			}
		
		if (keys['V'])
			lightEngine->specularSize += increment;
		if (keys['C'])
			lightEngine->specularStrength += increment * .005f;
		if (keys['X'])
			lightEngine->diffuseStrength += increment * .005f;
		if (keys['Z'])
			lightEngine->ambientStrength += increment * .001f;

		if (keys['N'])
		{
			lightEngine->specularStrength = 0.f;
			lightEngine->diffuseStrength = 0.f;
			lightEngine->ambientStrength = 0.f;
		}
		if (keys['M'])
		{
			lightEngine->specularStrength = 0.5f;
			lightEngine->diffuseStrength = 0.5f;
			lightEngine->ambientStrength = 0.2f;
		}

		const auto camera = scene->ActiveCamera;
		if (increment != 0 && keysActive == 2)
			_selectedLight->Configuration.GlobalStrength += increment * 0.01;

		const float speed = 0.2f;
		if (keys['W'])
			_selectedLight->Position -= *(camera->Front) * speed;
		if (keys['S'])
			_selectedLight->Position += *(camera->Front) * speed;
		if (keys['A'])
			_selectedLight->Position -= *(camera->Right) * speed;
		if (keys['D'])
			_selectedLight->Position += *(camera->Right) * speed;
		if (keys['E'])
			_selectedLight->Position -= *(camera->Up) * speed;
		if (keys['Q'])
			_selectedLight->Position += *(camera->Up) * speed;

		*_selectedLight->ModelMatrix = glm::scale(
			glm::translate(glm::mat4(1.f), _selectedLight->Position), 
			glm::vec3(0.2*_selectedLight->Configuration.GlobalStrength, 0.2*_selectedLight->Configuration.GlobalStrength, 0.2*_selectedLight->Configuration.GlobalStrength)
		);
		return false;
	}
	if (keys['K'] && keys['C'])
		system("cls");
	return true;
}
