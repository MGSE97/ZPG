#pragma once
#include <glm/vec3.hpp>
#include "Object.h"
#include <glm/common.hpp>
#include <glm/common.hpp>

namespace Engine {
	namespace Components {
		namespace Graphics {
			class Material;
		}
	}
}

class Light : public Engine::Objects::Object
{
public:
	glm::vec3 Position;
	float Power;
	glm::vec3 Color;
	glm::vec4 fColor;
	Light(Engine::Components::Graphics::Program* program, glm::vec3 position, float power = 1.f, glm::vec3 color = glm::vec3(1.f, 1.f, 1.f));
	~Light();
	Light* Use(Engine::Components::Graphics::Material* material);
};
