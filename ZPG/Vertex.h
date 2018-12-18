#pragma once
#include <glm/vec3.hpp>

class Vertex
{
public:
	Vertex() = default;
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 UV;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
};
