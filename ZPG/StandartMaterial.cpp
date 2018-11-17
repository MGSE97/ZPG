#include "StandartMaterial.h"

Application::Materials::StandartMaterial::StandartMaterial(glm::vec4 color)
{
	Color = color;
	Add("material.lightConfiguration", &Light);
	Add("material.color", &Color);
}

Application::Materials::StandartMaterial::StandartMaterial(Engine::Components::Graphics::Shader* shader, glm::vec4 color) : Material(shader)
{
	Color = color;
	Add("material.lightConfiguration", &Light);
	Add("material.color", &Color);
}
