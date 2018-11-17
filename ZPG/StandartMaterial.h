#pragma once
#include "Material.h"
#include "LightConfiguration.h"
#include "Shader.h"

namespace Application
{
	namespace Materials
	{
		class StandartMaterial : public Engine::Components::Graphics::Material
		{
		public:
			Engine::Components::Graphics::LightConfiguration Light{};
			glm::vec4 Color{};
			StandartMaterial(glm::vec4 color = glm::vec4(1));
			StandartMaterial(Engine::Components::Graphics::Shader* shader, glm::vec4 color = glm::vec4(1));
		};
	}
}

