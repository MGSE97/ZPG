#pragma once
#include "Material.h"
#include "VertexAttributeObject.h"
#include "VertexObject.h"
#include "Object.h"

namespace Engine
{
	namespace Objects
	{
		class Sphere : public Objects::Object
		{
		public:
			~Sphere();
			Sphere(Components::Graphics::Material* material, const float* points, int size, int dimensions);
			Sphere* Draw();
		};
	}
}
