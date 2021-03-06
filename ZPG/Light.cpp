﻿#include "Light.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include "Assets/Models/2/spheref.h"
#include "Assets/Models/2/plain.h"
#include "GenericSphere.h"
#include "GenericOctahedon.h"

Engine::Components::Light* Engine::Components::Light::Use(Graphics::Material* material, unsigned int index)
{
	/*material->Values->Add(
		new Engine::Components::Graphics::MaterialValue<glm::vec3>(
			material->Program->Shaders->Get("vertex"), "light.position", &Position)
	).Add(
		new Engine::Components::Graphics::MaterialValue<float>(
			material->Program->Shaders->Get("fragment"), "lightStrength", &Power)
	).Add(
		new Engine::Components::Graphics::MaterialValue<glm::vec3>(
			material->Program->Shaders->Get("fragment"), "lightColor", &Color)
	);*/
	material->Add("light[" + std::to_string(index) + "].position", Transform->GetPosition());
	material->Add("light[" + std::to_string(index) + "].configuration", &Configuration);
	return this;
}

Engine::Components::Light::Light(Graphics::Shader* shader, glm::vec3 position, glm::vec4 color, Graphics::LightConfiguration* configuration) :
	Object(new Application::Materials::StandartMaterial(shader), Engine::Objects::GenericOctahedon::GetInstance()->vertices, 3, false, false, true, Engine::Objects::GenericOctahedon::GetInstance()->indices)
	//Object(new Application::Materials::StandartMaterial(shader),(new Engine::Objects::GenericSphere(1.0f, 9, 9))->array, 3, true, true) //, sphere, 17280)// 
{
	//Position = position;
	if (configuration != nullptr)
	{
		Configuration.AmbientColor = configuration->AmbientColor;
		Configuration.DiffuseColor = configuration->DiffuseColor;
		Configuration.SpecularColor = configuration->SpecularColor;
		Configuration.AmbientStrength = configuration->AmbientStrength;
		Configuration.DiffuseStrength = configuration->DiffuseStrength;
		Configuration.SpecularStrength = configuration->SpecularStrength;
		Configuration.SpecularSize = configuration->SpecularSize;
		Configuration.GlobalStrength = configuration->GlobalStrength;
	}
	else
	{
		Configuration.AmbientStrength = 0.f;
		Configuration.DiffuseStrength = 1.f;
		Configuration.SpecularStrength = 1.f;
	}
	Configuration.UseLighting = true;
	Configuration.IsLight = true;
	Color = color;
	Transform->Position(position, true);
	Transform->Scale(0.2f * Configuration.GlobalStrength, true);
	//*ModelMatrix = *(new glm::mat4(glm::scale(glm::translate(*ModelMatrix, position), glm::vec3(0.2*Configuration.GlobalStrength, 0.2*Configuration.GlobalStrength, 0.2*Configuration.GlobalStrength))));
	Material->Add("material.color", &Color);
	Material->Add("material.lightConfiguration.useLighting", new bool(false));
}
