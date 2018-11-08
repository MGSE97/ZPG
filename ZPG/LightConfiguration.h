#pragma once
#include <glm/vec3.hpp>
#include <string>
#include "MaterialValueBase.h"

namespace Engine
{
	namespace Components
	{
		namespace Graphics
		{
			class LightConfiguration : public IMaterialStructure
			{
			public:
				glm::vec3 AmbientColor;
				float AmbientStrength;

				glm::vec3 DiffuseColor;
				float DiffuseStrength;

				glm::vec3 SpecularColor;
				float SpecularStrength;

				float GlobalStrength;
				int SpecularSize;
				bool UseLighting;

				bool IsLight;

				LightConfiguration();

				void SetUniforms(Shader* shader, Program* program, std::string parentName) override;
			};
		}
	}
}
