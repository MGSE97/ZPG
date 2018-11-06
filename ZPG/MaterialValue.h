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
				MaterialValue(Graphics::Shader* shader, std::string property, T* value) : MaterialValueBase(shader, property)
				{
					Value = value;
				}
				T* Value;
				void Set(Program* program) override
				{
					Shader->SendUniform(program, Property, Value);
				}
			};
		}
	}
}

