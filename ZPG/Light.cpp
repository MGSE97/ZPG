#include "Light.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include "Assets/Models/2/spheref.h"

Light::Light(Engine::Components::Graphics::Program* program, glm::vec3 position, float power, glm::vec3 color) : Object(new Engine::Components::Graphics::Material(program), sphere, 17280)
{
	Position = position;
	Power = power;
	Color = color;

	fColor = glm::vec4(255.f*color.x, 255.f*color.y, 255.f*color.z, power);

	*ModelMatrix = *(new glm::mat4(glm::scale(glm::translate(*ModelMatrix, position), glm::vec3(0.2*power, 0.2*power, 0.2*power))));

	Material->Values->Add(
		new Engine::Components::Graphics::MaterialValue<glm::vec4>(
			program->Shaders->Get("fragment"), "color", &fColor)
	).Add(new Engine::Components::Graphics::MaterialValue<bool>(
		program->Shaders->Get("fragment"), "useLighting", new bool(false)
	));;
	//Use(Material);
}

Light* Light::Use(Engine::Components::Graphics::Material* material)
{
	material->Values->Add(
		new Engine::Components::Graphics::MaterialValue<glm::vec3>(
			material->Program->Shaders->Get("vertex"), "lightPos", &Position)
	).Add(
		new Engine::Components::Graphics::MaterialValue<float>(
			material->Program->Shaders->Get("fragment"), "lightStrength", &Power)
	).Add(
		new Engine::Components::Graphics::MaterialValue<glm::vec3>(
			material->Program->Shaders->Get("fragment"), "lightColor", &Color)
	);

	return this;
}
