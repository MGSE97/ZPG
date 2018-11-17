#define GLM_ENABLE_EXPERIMENTAL
//#define DEBUG
#include "Shader.h"
#include <cstddef>
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <glm/gtx/string_cast.hpp>
#include <cstdio>
#include <sstream>
#include <fstream>
#include <vector>

Engine::Components::Graphics::Shader::Shader()
{
	_compiled = false;
	Shaders = new Generic::Dictionary<std::string, GLuint>();
	_program = glCreateProgram();
}

Engine::Components::Graphics::Shader::~Shader()
{
	/*delete _code;
	delete &_compiled;
	delete &_shader;*/
}

Engine::Components::Graphics::Shader* Engine::Components::Graphics::Shader::Add(std::string key, int type, std::string filename)
{
	_compiled = false;
	std::ifstream file(filename, std::ios::in);
	if (file.is_open())
	{
		std::stringstream buffer;
		buffer << file.rdbuf();
		std::string sh = buffer.str();
		file.close();
		const auto version = sh.find_first_of('#');
		sh = sh.substr(version, sh.length() - version);

		const char* shader = sh.data();

		Shaders->Add(key, glCreateShader(type));
		glShaderSource(Shaders->Get(key), 1, &shader, NULL);
	}
	return this;
}

Engine::Components::Graphics::Shader* Engine::Components::Graphics::Shader::Add(std::string key, int type, const char* shader)
{
	Shaders->Add(key, glCreateShader(type));
	glShaderSource(Shaders->Get(key), 1, &shader, NULL);
	return this;
}


Engine::Components::Graphics::Shader* Engine::Components::Graphics::Shader::Use()
{
	glUseProgram(Get());
	return this;
}

bool Engine::Components::Graphics::Shader::Compile()
{
	bool failed = false;
	GLint data = 0;
	for (const auto& pair : *Shaders)
	{
		glCompileShader(pair.second);
		glGetShaderiv(pair.second, GL_COMPILE_STATUS, &data);
		if (data == GL_FALSE)
		{
			failed = true;
			glGetShaderiv(pair.second, GL_INFO_LOG_LENGTH, &data);

			// The maxLength includes the NULL character
			std::vector<char> errorLog(data);
			glGetShaderInfoLog(pair.second, data, &data, &errorLog[0]);

			fprintf(stderr, "Shader %s Compilation failed:\nErrors:\n%s\n", pair.first.c_str(), errorLog.data());
		}
		else
			glAttachShader(_program, pair.second);
	}
	if(!failed)
	{
		glLinkProgram(_program); 
		glGetProgramiv(_program, GL_LINK_STATUS, &data);
		if (data == GL_FALSE)
		{
			GLint infoLogLength;
			glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &infoLogLength);
			GLchar *strInfoLog = new GLchar[infoLogLength + 1];
			glGetProgramInfoLog(_program, infoLogLength, NULL, strInfoLog);
			fprintf(stderr, "Linker failure: %s\n", strInfoLog);
			delete[] strInfoLog;
			failed = true;
		}
	}
	_compiled = !failed;
	return _compiled;
}

GLuint Engine::Components::Graphics::Shader::Get()
{
	if (!_compiled)
		Compile();
	return _program;
}


Engine::Components::Graphics::Shader* Engine::Components::Graphics::Shader::SendUniform(std::string name, IMaterialStructure* data)
{
	#ifdef DEBUG
		fprintf(stderr, "SET IMS: %s (0x%p)\n", name.c_str(), data);
	#endif

	data->SetUniforms(this, name);

	return this;
}

Engine::Components::Graphics::Shader* Engine::Components::Graphics::Shader::SendUniform(std::string name, glm::mat4* data)
{
	#ifdef DEBUG
		fprintf(stderr, "SET MAT4: %s (0x%p) value \n%s\n", name.c_str(), data, Mat4ToString(*data).c_str());
	#endif
	GLint uniformID = glGetUniformLocation(Get(), static_cast<const GLchar*>(name.c_str()));
	if (uniformID >= 0) {
		glUniformMatrix4fv(uniformID, 1, GL_FALSE, value_ptr(*data));
	}
	else {
		fprintf(stderr, "ERROR: program %u mat4 variable %s not found\n", _program, name.c_str());
	}

	return this;
}

Engine::Components::Graphics::Shader* Engine::Components::Graphics::Shader::SendUniform(std::string name, glm::vec4* data)
{
	#ifdef DEBUG
		fprintf(stderr, "SET VEC4: %s (0x%p) value \n(%f, %f, %f, %f)\n", name.c_str(), data, data->x, data->y, data->z, data->w);
	#endif
	GLint uniformID = glGetUniformLocation(Get(), static_cast<const GLchar*>(name.c_str()));
	if (uniformID >= 0) {
		glUniform4f(uniformID, data->x, data->y, data->z, data->w);
	}
	else {
		fprintf(stderr, "ERROR: program %u vec4 variable %s not found\n", _program, name.c_str());
	}

	return this;
}

Engine::Components::Graphics::Shader* Engine::Components::Graphics::Shader::SendUniform(std::string name, glm::vec3* data)
{
	#ifdef DEBUG
		fprintf(stderr, "SET VEC3: %s (0x%p) value \n(%f, %f, %f)\n", name.c_str(), data, data->x, data->y, data->z);
	#endif
	GLint uniformID = glGetUniformLocation(Get(), static_cast<const GLchar*>(name.c_str()));
	if (uniformID >= 0) {
		glUniform3f(uniformID, data->x,data->y,data->z);
	}
	else {
		fprintf(stderr, "ERROR: program %u vec3 variable %s not found\n", _program, name.c_str());
	}

	return this;
}


Engine::Components::Graphics::Shader* Engine::Components::Graphics::Shader::SendUniform(std::string name, float* data)
{
	#ifdef DEBUG
		fprintf(stderr, "SET FLOAT: %s (0x%x) value %f\n", name.c_str(), data, *data);
	#endif
	GLint uniformID = glGetUniformLocation(Get(), static_cast<const GLchar*>(name.c_str()));
	if (uniformID >= 0) {
		glUniform1f(uniformID, *data);
	}
	else {
		fprintf(stderr, "ERROR: program %u float variable %s not found\n", _program, name.c_str());
	}

	return this;
}

Engine::Components::Graphics::Shader* Engine::Components::Graphics::Shader::SendUniform(std::string name, int* data)
{
	#ifdef DEBUG
		fprintf(stderr, "SET INT: %s (0x%p) value %d\n", name.c_str(), data, *data);
	#endif
	GLint uniformID = glGetUniformLocation(Get(), static_cast<const GLchar*>(name.c_str()));
	if (uniformID >= 0) {
		glUniform1i(uniformID, *data);
	}
	else {
		fprintf(stderr, "ERROR: program %u int variable %s not found\n", _program, name.c_str());
	}

	return this;
}

Engine::Components::Graphics::Shader* Engine::Components::Graphics::Shader::SendUniform(std::string name, bool* data)
{
	#ifdef DEBUG
		fprintf(stderr, "SET BOOL: %s (0x%p) value %b\n", name.c_str(), data, *data);
	#endif
	GLint uniformID = glGetUniformLocation(Get(), static_cast<const GLchar*>(name.c_str()));
	if (uniformID >= 0) {
		glUniform1i(uniformID, *data);
	}
	else {
		fprintf(stderr, "ERROR: program %u int variable %s not found\n", _program, name.c_str());
	}

	return this;
}

std::string Engine::Components::Graphics::Shader::Mat4ToString(glm::mat4& mat)
{
	char* txt = new char[200];
	sprintf_s(txt, 200, "%6.4f\t%6.4f\t%6.4f\t%6.4f\n%6.4f\t%6.4f\t%6.4f\t%6.4f\n%6.4f\t%6.4f\t%6.4f\t%6.4f\n%6.4f\t%6.4f\t%6.4f\t%6.4f",
		mat[0][0], mat[0][1], mat[0][2], mat[0][3],
		mat[1][0], mat[1][1], mat[1][2], mat[1][3],
		mat[2][0], mat[2][1], mat[2][2], mat[2][3],
		mat[3][0], mat[3][1], mat[3][2], mat[3][3]);
	/*txt << mat[0][0] << "\t\t" << mat[0][1] << "\t\t" << mat[0][2] << "\t\t" << mat[0][3] << std::endl;
	txt << mat[1][0] << "\t\t" << mat[1][1] << "\t\t" << mat[1][2] << "\t\t" << mat[1][3] << std::endl;
	txt << mat[2][0] << "\t\t" << mat[2][1] << "\t\t" << mat[2][2] << "\t\t" << mat[2][3] << std::endl; 
	txt << mat[3][0] << "\t\t" << mat[3][1] << "\t\t" << mat[3][2] << "\t\t" << mat[3][3] << std::endl;*/
	return std::string(txt);
}
