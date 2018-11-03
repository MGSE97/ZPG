#pragma once
#include <GL/glew.h>
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
				MaterialValueBase(Shader* shader, const GLchar* property)
				{
					Shader = shader;
					Property = property;
				}
				virtual ~MaterialValueBase() = default;
				Shader* Shader;
				const GLchar* Property;
				virtual void Set(Graphics::Program* program) = 0;
			};
		}
	}
}
