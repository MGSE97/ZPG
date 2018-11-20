#include "LightConfiguration.h"
#include <string>

Engine::Components::Graphics::LightConfiguration::LightConfiguration()
{
	AmbientColor = glm::vec3(1.f,1.f,1.f);
	DiffuseColor = glm::vec3(1.f,1.f,1.f);
	SpecularColor = glm::vec3(1.f,1.f,1.f);

	AmbientStrength = 0.1f;
	DiffuseStrength = 0.3f;
	SpecularStrength = 0.5f;

	SpecularSize = 4;

	GlobalStrength = 1.f;

	UseLighting = true;

	IsLight = false;
}

void Engine::Components::Graphics::LightConfiguration::SetUniforms(Engine::Components::Graphics::Shader* shader, std::string parentName)
{
	auto prefix = parentName + ".";

	shader->SendUniform(prefix + "ambientColor", &AmbientColor);
	shader->SendUniform(prefix + "diffuseColor", &DiffuseColor);
	shader->SendUniform(prefix + "specularColor", &SpecularColor);

	shader->SendUniform(prefix + "ambientStrength", &AmbientStrength);
	shader->SendUniform(prefix + "diffuseStrength", &DiffuseStrength);
	shader->SendUniform(prefix + "specularStrength", &SpecularStrength);

	shader->SendUniform(prefix + "globalStrength", &GlobalStrength);
	if(!IsLight)
	{
		shader->SendUniform(prefix + "specularSize", &SpecularSize);
		shader->SendUniform(prefix + "useLighting", &UseLighting);
	}
}