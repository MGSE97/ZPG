#pragma once
#include <GL/glew.h>
#include <glm/vec4.hpp>
#include <glm/mat4x2.hpp>
#include <xstring>
#include "MaterialValueType.h"
#include <string>


namespace Engine
{
	namespace Components
	{
		namespace Graphics
		{
			class Program;

			class Shader
			{
			public:
				Shader(int type, std::string filename);
				Shader(int type, const char* shader);
				~Shader();
				Shader* Compile();
				GLuint* Get();
				Shader* SendUniform(Program* program, const GLchar* name, glm::mat4* data);
				Shader* SendUniform(Program* program, const GLchar* name, glm::vec4* data);
				Shader* SendUniform(Program* program, const GLchar* name, glm::vec3* data);
				Shader* SendUniform(Program* program, const GLchar* name, float* data);
				Shader* SendUniform(Program* program, const GLchar* name, int* data);
				Shader* SendUniform(Program* program, const GLchar* name, bool* data);
				void setData(Program* program, const GLchar* property, MaterialValueType type, void* value);
			private:
				GLuint _shader;
				bool _compiled;
				char* _code;
				std::string Mat4ToString(glm::mat4& mat);
			};
		}
	}
}

