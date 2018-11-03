#pragma once
#include "VertexObject.h"

namespace Engine
{
	namespace Objects
	{
		class Object : public Components::Objects::VertexObject
		{
		public:
			glm::mat4* ModelMatrix;
			Object(Components::Graphics::Material* material, const float* points, int size, int dimensions = 3, int startArrayIndex = 0);
			Object(Components::Graphics::Material* material, const float* points, int size, int dimensions, Generic::Collection<Components::Objects::VAOConfig*> configs);
			~Object();
		};
	}
}
