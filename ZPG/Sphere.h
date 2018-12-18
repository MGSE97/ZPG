#pragma once
#include "Material.h"
#include "VertexAttributeObject.h"
#include "VertexObject.h"
#include "Object.h"

namespace Engine
{
	namespace Objects
	{
		class Sphere : public Components::Objects::Object
		{
		public:
			~Sphere();
			Sphere(Application::Materials::StandartMaterial* material, const float* points, int size, int dimensions);
			Sphere* Draw();
		};
	}
}
