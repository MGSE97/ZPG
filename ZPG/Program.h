#pragma once
#include <GL/glew.h>
#include "Collection.h"
#include "Dictionary.h"
#include <string>

namespace Engine
{
	namespace Components
	{
		namespace Graphics
		{
			class Shader;

			class Program
			{
			public:
				Program();
				~Program();
				Program* AddShader(std::string key, Shader* shader);
				Program* AddShaders(Generic::Dictionary<std::string, Shader*>* shaders);
				Program* Link();
				Program* Use();
				GLuint* Get();
				Generic::Dictionary<std::string, Shader*>* Shaders;
			private:
				GLuint _program;
				bool _linked;
				bool CheckLink();
			};
		}
	}
}
