#pragma once
#include "BaseEngine.h"
#include <glm/common.hpp>

namespace Application
{
	namespace Engines
	{
		class LightEngine : public Engine::BaseEngine
		{
		public:
			LightEngine* Init(std::FILE* errorStream = stderr) override;
			void Update(::Engine::Components::Window* window) override;
			/*float ambientStrength;
			float diffuseStrength;
			float specularStrength;
			glm::vec3 ambientColor;
			glm::vec3 diffuseColor;
			glm::vec3 specularColor;
			int specularSize;*/
		private:
			//glm::mat4 M;
			float angle;
		};
	}
}

