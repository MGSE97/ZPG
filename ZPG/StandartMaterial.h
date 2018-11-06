#pragma once
#include "Material.h"
#include "LightConfiguration.h"

namespace Application
{
	namespace Materials
	{
		class StandartMaterial : public Engine::Components::Graphics::Material
		{
		public:
			Engine::Components::Graphics::LightConfiguration Light;
			glm::vec4 Color{};
			StandartMaterial(Engine::Components::Graphics::Program* program, glm::vec4 color = glm::vec4(1));
		};
	}
}

