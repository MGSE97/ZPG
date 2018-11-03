#pragma once
#include <string>
#include "Shader.h"

class ProgramDataKey
{
public:
	ProgramDataKey(Engine::Components::Shader* shader, std::string property)
	{
		Shader = shader;
		Property = property;
	}
	Engine::Components::Shader* Shader;
	std::string Property;
};

