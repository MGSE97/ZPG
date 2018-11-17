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
				MaterialValueBase(std::string property)
				{
					Property = property;
				}
				virtual ~MaterialValueBase() = default;
				std::string Property;
				virtual void Set(Shader* shader) = 0;
			};
		}
	}
}
