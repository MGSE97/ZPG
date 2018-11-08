#include "LightConfiguration.h"
#include <string>

Engine::Components::Graphics::LightConfiguration::LightConfiguration()
{
	AmbientColor = glm::vec3(1.f,1.f,1.f);
	DiffuseColor = glm::vec3(1.f,1.f,1.f);
	SpecularColor = glm::vec3(1.f,1.f,1.f);

	AmbientStrength = 0.1f;
	DiffuseStrength = 0.5f;
	SpecularStrength = 0.5f;

	SpecularSize = 4;

	GlobalStrength = 1.f;

	UseLighting = true;

	IsLight = false;
}

void Engine::Components::Graphics::LightConfiguration::SetUniforms(Engine::Components::Graphics::Shader* shader, Engine::Components::Graphics::Program* program, std::string parentName)
{
	auto prefix = parentName + ".";

	shader->SendUniform(program, prefix + "ambientColor", &AmbientColor);
	shader->SendUniform(program, prefix + "diffuseColor", &DiffuseColor);
	shader->SendUniform(program, prefix + "specularColor", &SpecularColor);

	shader->SendUniform(program, prefix + "ambientStrength", &AmbientStrength);
	shader->SendUniform(program, prefix + "diffuseStrength", &DiffuseStrength);
	shader->SendUniform(program, prefix + "specularStrength", &SpecularStrength);

	shader->SendUniform(program, prefix + "globalStrength", &GlobalStrength);
	if(!IsLight)
	{
		shader->SendUniform(program, prefix + "specularSize", &SpecularSize);
		shader->SendUniform(program, prefix + "useLighting", &UseLighting);
	}
}