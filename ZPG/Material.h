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
				Shader* Shader;
				Material();
				Material(Graphics::Shader* shader);
				virtual ~Material();
				Material* SetShader(Graphics::Shader* shader);
				Material* Use();
				Generic::Collection<MaterialValueBase*>* Values;
				template<typename T>
				Material* Add(std::string property, T* value)
				{
					Values->Add(new MaterialValue<T>(property, value));
					return this;
				}
			};
		}
	}
}


