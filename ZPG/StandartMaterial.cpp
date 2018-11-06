#include "StandartMaterial.h"

Application::Materials::StandartMaterial::StandartMaterial(Engine::Components::Graphics::Program* program, glm::vec4 color) : Material(program)
{
	Color = color;
	if (program != nullptr)
		Add(program->Shaders->First(), "material.lightConfiguration", &Light);
	Add(program->Shaders->First(), "material.color", &Color);
}
