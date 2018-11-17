#pragma once
#include <string>
#include "Shader.h"
#include "MaterialValueBase.h"

namespace Engine
{
	namespace Components
	{
		namespace Graphics
		{
			template<typename T>
			class MaterialValue : public MaterialValueBase
			{
			public:
				MaterialValue(std::string property, T* value) : MaterialValueBase(property)
				{
					Value = value;
				}
				T* Value;
				void Set(Shader* shader) override
				{
					shader->SendUniform(Property, Value);
				}
			};
		}
	}
}

