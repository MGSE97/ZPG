#include "LightingChangeInputHandler.h"
#include <glm/ext/matrix_transform.hpp>
#include "LigtEngine.h"
#include "StandartMaterial.h"
#include "Sphere.h"
#include "Assets/Models/2/spheref.h"

bool Application::Input::Handlers::LightingChangeInputHandler::HandleKeys(Engine::BaseEngine* engine, Engine::Components::Window* window, Engine::Components::Scene* scene, Generic::Dictionary<short, bool>& keys, int keysActive)
{
	if (keys['L'] && dynamic_cast<Application::Engines::LightEngine*>(engine) != nullptr)
	{
		if (_selectedLight == nullptr)
			_selectedLight = scene->Lights->First();
		auto lightEngine = dynamic_cast<Application::Engines::LightEngine*>(engine);

		const auto increment = (keys['R'] ? 1 : (keys['F'] ? -1 : 0));


		if (scene != nullptr && scene->Objects != nullptr && !scene->Objects->empty())
			if (keys['O'] && keys['C'])
			{
				std::string prefix("created_lchih_");
				auto keys = new Generic::Collection<std::string>();
				for (auto& it : *scene->Objects)
				{
					if (strncmp(it.first.c_str(), prefix.c_str(), prefix.size()) == 0)
					{
						delete it.second;
						keys->Add(it.first);
					}
				}
				for (auto& key : *keys)
					scene->Objects->erase(key);
				keys->clear();
				delete keys;
			}
			else
			for (auto& it : *scene->Objects)
			{
				auto* material = dynamic_cast<Materials::StandartMaterial*>(it.second->Material);
				if (material == nullptr)
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

				if (keys['K'])
				{
					const auto zeroIncrement = increment / 2.0f + 0.5f;
					if (increment > 0 && keys['V'])
					{
						mlc->SpecularStrength = 0.5f;
						mlc->DiffuseStrength = 0.5f;
						mlc->AmbientStrength = 0.2f;
					}
					else if (increment < 0 && keys['V'])
					{
						mlc->SpecularStrength = 0.f;
						mlc->DiffuseStrength = 0.f;
						mlc->AmbientStrength = 0.f;
					}
					else {
						if (keys['C'])
							mlc->SpecularStrength = zeroIncrement;
						if (keys['X'])
							mlc->DiffuseStrength = zeroIncrement;
						if (keys['Z'])
							mlc->AmbientStrength = zeroIncrement;
					}
				}
			}
		
		/*if (keys['V'])
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
		}*/

		const auto camera = scene->ActiveCamera;
		if (increment != 0 && keysActive == 2)
		{
			_selectedLight->Configuration.GlobalStrength += increment * 0.01;
			_selectedLight->Transform->Scale(0.2f * _selectedLight->Configuration.GlobalStrength, true);
		}

		const float speed = 0.2f;
		if (keys['W'])
			_selectedLight->Transform->Position(-*(camera->Front) * speed);
		if (keys['S'])
			_selectedLight->Transform->Position(*(camera->Front) * speed);
		if (keys['A'])
			_selectedLight->Transform->Position(-*(camera->Right) * speed);
		if (keys['D'])
			_selectedLight->Transform->Position(*(camera->Right) * speed);
		if (keys['E'])
			_selectedLight->Transform->Position(-*(camera->Up) * speed);
		if (keys['Q'])
			_selectedLight->Transform->Position(*(camera->Up) * speed);
		
		/**_selectedLight->ModelMatrix = glm::scale(
			glm::translate(glm::mat4(1.f), _selectedLight->Position), 
			glm::vec3(0.2*_selectedLight->Configuration.GlobalStrength, 0.2*_selectedLight->Configuration.GlobalStrength, 0.2*_selectedLight->Configuration.GlobalStrength)
		);*/
		return false;
	}
	if (keys['K'] && keys['C'])
		system("cls");
	return true;
}

bool Application::Input::Handlers::LightingChangeInputHandler::HandleMouse(Engine::BaseEngine* engine, Engine::Components::Window* window, Engine::Components::Scene* scene, double x, double y, Generic::Dictionary<short, bool>& keys, int keysActive)
{
	if (scene != nullptr && scene->Objects != nullptr && !scene->Objects->empty())
	{
		for (auto& it : *scene->Objects)
		{
			auto* material = dynamic_cast<Materials::StandartMaterial*>(it.second->Material);
			if (material == nullptr)
				continue;

			if (it.second->IsClicked(&engine->WorldObjectId) && keys[MK_L])
				material->Color = glm::vec4(1) - material->Color;
		}

		if (keys[MK_C])
		{
			auto mat = new Materials::StandartMaterial(engine->Programs->Get("basic"), glm::vec4(0.f, 255.f, 0.f, 1.f));
			auto obj = new Engine::Objects::Sphere(mat, sphere, 17280, 3);
			obj->Transform->Position(engine->WorldPosition, true);
			obj->Transform->Scale(0.1f, true);
			scene->Objects->Add("created_lchih_" + std::to_string(obj->Id), obj);
		}
	}
	return true;
}
