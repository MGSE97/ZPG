#pragma once
#include <glm/vec3.hpp>
#include "Object.h"
#include <glm/common.hpp>
#include <glm/common.hpp>
#include "LightConfiguration.h"

namespace Engine {
	namespace Components {
		namespace Graphics {
			class Material;
		}

		class Light : public Engine::Objects::Object
		{
		public:
			//glm::vec3 Position;
			Graphics::LightConfiguration Configuration;
			/*float Power;*/
			glm::vec4 Color;
			Light(Graphics::Program* program, glm::vec3 position, glm::vec4 color, Graphics::LightConfiguration* configuration);
			~Light();
			Light* Use(Graphics::Material* material);
		};
	}
}

