#pragma once
#include "Shader.h"

namespace Engine
{
	namespace Components
	{
		namespace Graphics
		{
			class MaterialValueBase
			{
			public:
				MaterialValueBase(Shader* shader, std::string property)
				{
					Shader = shader;
					Property = property;
				}
				virtual ~MaterialValueBase() = default;
				Shader* Shader;
				std::string Property;
				virtual void Set(Graphics::Program* program) = 0;
			};
		}
	}
}
