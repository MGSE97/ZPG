#pragma once
#include <GL/glew.h>
#include <glm/vec4.hpp>
#include <glm/mat4x2.hpp>
#include <xstring>
#include <string>

namespace Engine
{
	namespace Components
	{

		namespace Graphics
		{
			class Shader;
			class Program;
			__interface IMaterialStructure
			{
			public:
				virtual void SetUniforms(Shader* shader, Program* program, std::string parentName) = 0;
			};

			class Shader
			{
			public:
				Shader(int type, std::string filename);
				Shader(int type, const char* shader);
				~Shader();
				Shader* Compile();
				GLuint* Get();
				Shader* SendUniform(Program* program, std::string name, IMaterialStructure* data);
				Shader* SendUniform(Program* program, std::string name, glm::mat4* data);
				Shader* SendUniform(Program* program, std::string name, glm::vec4* data);
				Shader* SendUniform(Program* program, std::string name, glm::vec3* data);
				Shader* SendUniform(Program* program, std::string name, float* data);
				Shader* SendUniform(Program* program, std::string name, int* data);
				Shader* SendUniform(Program* program, std::string name, bool* data);
			private:
				GLuint _shader;
				bool _compiled;
				char* _code;
				std::string Mat4ToString(glm::mat4& mat);
			};
		}
	}
}

