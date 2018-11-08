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
				virtual ~Material();
				Material* Use();
				Generic::Collection<MaterialValueBase*>* Values;
				template<typename T>
				Material* Add(Shader * shader, std::string property, T * value)
				{
					Values->Add(new MaterialValue<T>(shader, property, value));
					return this;
				}
			};
		}
	}
}


