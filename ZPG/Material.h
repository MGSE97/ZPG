#pragma once
#include "Dictionary.h"
#include <string>
#include "MaterialValue.h"
#include "Program.h"
#include "Shader.h"

namespace Engine
{
	namespace Components
	{
		namespace Graphics
		{
			class Material
			{
			public:
				Program* Program;
				Material(Graphics::Program* program);
				~Material();
				Material* Use();
				Generic::Collection<MaterialValueBase*>* Values;
				template<typename T>
				Material* Add(Shader * shader, const GLchar * property, T * value);
			};
		}
	}
}


