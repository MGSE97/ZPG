#pragma once
#include "Material.h"
#include "LightConfiguration.h"
#include "Shader.h"
#include "Texture.h"

namespace Application
{
	namespace Materials
	{
		class StandartMaterial : public Engine::Components::Graphics::Material
		{
		public:
			Generic::Dictionary<std::string, Engine::Components::Graphics::Texture*>* Textures;
			Engine::Components::Graphics::LightConfiguration Light{};
			glm::vec4 Color;
			bool HasDiffuseTexture;
			bool HasNormalTexture;
			StandartMaterial(glm::vec4 color = glm::vec4(1));
			StandartMaterial(Engine::Components::Graphics::Shader* shader, glm::vec4 color = glm::vec4(1));
			StandartMaterial* Use() override;
		};
	}
}

