#pragma once
#include <GL/glew.h>
#include <glm/vec4.hpp>
#include <glm/mat4x2.hpp>
#include <xstring>
#include <string>
#include "Dictionary.h"

namespace Engine
{
	namespace Components
	{
		namespace Graphics
		{
			class Shader;
			__interface IMaterialStructure
			{
			public:
				virtual void SetUniforms(Shader* shader, std::string parentName) = 0;
			};

			class Shader
			{
			public:
				Generic::Dictionary<std::string, GLuint>* Shaders;
				Shader();
				~Shader();
				Shader* Add(std::string key, int type, std::string filename);
				Shader* Add(std::string key, int type, const char* shader);
				Shader* Use();
				bool Compile();
				Shader* SendUniform(std::string name, IMaterialStructure* data);
				Shader* SendUniform(std::string name, glm::mat4* data);
				Shader* SendUniform(std::string name, glm::vec4* data);
				Shader* SendUniform(std::string name, glm::vec3* data);
				Shader* SendUniform(std::string name, float* data);
				Shader* SendUniform(std::string name, int* data);
				Shader* SendUniform(std::string name, bool* data);
			private:
				GLuint Get();
				GLuint _program;
				bool _compiled;
				std::string Mat4ToString(glm::mat4& mat);
			};
		}
	}
}

