#include "StandartMaterial.h"

Application::Materials::StandartMaterial::StandartMaterial(glm::vec4 color)
{
	HasNormalTexture = false;
	HasDiffuseTexture = false;
	Color = color;
	Add("material.lightConfiguration", &Light);
	Add("material.color", &Color);
	Add("material.hasDiffuseTexture", &HasDiffuseTexture);
	Add("material.hasNormalTexture", &HasNormalTexture);
	Textures = new Generic::Dictionary<std::string, Engine::Components::Graphics::Texture*>;
}

Application::Materials::StandartMaterial::StandartMaterial(Engine::Components::Graphics::Shader* shader, glm::vec4 color) : Material(shader)
{
	HasNormalTexture = false;
	HasDiffuseTexture = false;
	Color = color;
	Add("material.lightConfiguration", &Light);
	Add("material.color", &Color);
	Add("material.hasDiffuseTexture", &HasDiffuseTexture);
	Add("material.hasNormalTexture", &HasNormalTexture);
	Textures = new Generic::Dictionary<std::string, Engine::Components::Graphics::Texture*>;
}

Application::Materials::StandartMaterial* Application::Materials::StandartMaterial::Use()
{
	Material::Use();

	if (Textures != nullptr && !Textures->empty())
		for (auto& texture : *Textures)
		{
			texture.second->Use(Shader, "material."+texture.first);
		}

	return this;
}

/*Application::Materials::StandartMaterial* Application::Materials::StandartMaterial::AddTexture(std::string name, Engine::Components::Graphics::Texture* texture)
{
	Textures->Add(name, texture);
}*/




