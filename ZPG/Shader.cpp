#define GLM_ENABLE_EXPERIMENTAL
#include "Shader.h"
#include <cstddef>
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <glm/gtx/string_cast.hpp>
#include <cstdio>
#include "Program.h"
#include "MaterialValueType.h"
#include <sstream>
#include <fstream>
#include <vector>

Engine::Components::Graphics::Shader::Shader(int type, std::string filename)
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

		_shader = glCreateShader(type);
		glShaderSource(_shader, 1, &shader, NULL);
		glCompileShader(_shader);
		/*
		// Handle Error
		GLint isCompiled = 0;
		glGetShaderiv(_shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(_shader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> errorLog(maxLength);
			glGetShaderInfoLog(_shader, maxLength, &maxLength, &errorLog[0]);

			fprintf(stderr, "Shader %u Compilation failed:\nCode:\n%s\nErrors:\n%s\n", _shader, shader, errorLog.data());
		}
		_compiled = isCompiled != GL_FALSE;*/
	}
}

Engine::Components::Graphics::Shader::Shader(int type, const char* shader)
{
	_shader = glCreateShader(type);
	glShaderSource(_shader, 1, &shader, NULL);
}

Engine::Components::Graphics::Shader::~Shader()
{
	/*delete _code;
	delete &_compiled;
	delete &_shader;*/
}

Engine::Components::Graphics::Shader* Engine::Components::Graphics::Shader::Compile()
{
	glCompileShader(_shader);
	GLint isCompiled = 0;
	glGetShaderiv(_shader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(_shader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(_shader, maxLength, &maxLength, &errorLog[0]);

		fprintf(stderr, "Shader %u Compilation failed:\nCode:\n%s\nErrors:\n%s\n", _shader, _code, errorLog.data());
	}
	_compiled = isCompiled != GL_FALSE;
	return this;
}

GLuint* Engine::Components::Graphics::Shader::Get()
{
	if (!_compiled)
		Compile();
	return &_shader;
}

Engine::Components::Graphics::Shader* Engine::Components::Graphics::Shader::SendUniform(Program* program, const GLchar* name, glm::mat4* data)
{
	#ifdef DEBUG
		fprintf(stderr, "SET MAT4: %s (0x%p) value \n%s\n", name, data, Mat4ToString(*data).c_str());
	#endif
	GLint uniformID = glGetUniformLocation(*(program->Get()), name);
	if (uniformID >= 0) {
		glUniformMatrix4fv(uniformID, 1, GL_FALSE, value_ptr(*data));
	}
	else {
		fprintf(stderr, "ERROR: program 0x%p:%u mat4 variable %s not found\n", program, *(program->Get()), name);
	}

	return this;
}

Engine::Components::Graphics::Shader* Engine::Components::Graphics::Shader::SendUniform(Program* program, const GLchar* name, glm::vec4* data)
{
	#ifdef DEBUG
		fprintf(stderr, "SET VEC4: %s (0x%p) value \n(%f, %f, %f, %f)\n", name, data, data->x, data->y, data->z, data->w);
	#endif
	GLint uniformID = glGetUniformLocation(*(program->Get()), name);
	if (uniformID >= 0) {
		glUniform4f(uniformID, data->x, data->y, data->z, data->w);
	}
	else {
		fprintf(stderr, "ERROR: program 0x%p:%u vec4 variable %s not found\n", program, *(program->Get()), name);
	}

	return this;
}

Engine::Components::Graphics::Shader* Engine::Components::Graphics::Shader::SendUniform(Program* program, const GLchar* name, glm::vec3* data)
{
	#ifdef DEBUG
		fprintf(stderr, "SET VEC3: %s (0x%p) value \n(%f, %f, %f)\n", name, data, data->x, data->y, data->z);
	#endif
	GLint uniformID = glGetUniformLocation(*(program->Get()), name);
	if (uniformID >= 0) {
		glUniform3f(uniformID, data->x,data->y,data->z);
	}
	else {
		fprintf(stderr, "ERROR: program 0x%p:%u vec3 variable %s not found\n", program, *(program->Get()), name);
	}

	return this;
}


Engine::Components::Graphics::Shader* Engine::Components::Graphics::Shader::SendUniform(Program* program, const GLchar* name, float* data)
{
	#ifdef DEBUG
		fprintf(stderr, "SET FLOAT: %s (0x%x) value %f\n", name, data, *data);
	#endif
	GLint uniformID = glGetUniformLocation(*(program->Get()), name);
	if (uniformID >= 0) {
		glUniform1f(uniformID, *data);
	}
	else {
		fprintf(stderr, "ERROR: program 0x%p:%u float variable %s not found\n", program, *(program->Get()), name);
	}

	return this;
}

Engine::Components::Graphics::Shader* Engine::Components::Graphics::Shader::SendUniform(Program* program, const GLchar* name, int* data)
{
	#ifdef DEBUG
		fprintf(stderr, "SET INT: %s (0x%p) value %d\n", name, data, *data);
	#endif
	GLint uniformID = glGetUniformLocation(*(program->Get()), name);
	if (uniformID >= 0) {
		glUniform1i(uniformID, *data);
	}
	else {
		fprintf(stderr, "ERROR: program 0x%p:%u int variable %s not found\n", program, *(program->Get()), name);
	}

	return this;
}

Engine::Components::Graphics::Shader* Engine::Components::Graphics::Shader::SendUniform(Program* program, const GLchar* name, bool* data)
{
	#ifdef DEBUG
		fprintf(stderr, "SET BOOL: %s (0x%p) value %b\n", name, data, *data);
	#endif
	GLint uniformID = glGetUniformLocation(*(program->Get()), name);
	if (uniformID >= 0) {
		glUniform1i(uniformID, *data);
	}
	else {
		fprintf(stderr, "ERROR: program 0x%p:%u int variable %s not found\n", program, *(program->Get()), name);
	}

	return this;
}

void Engine::Components::Graphics::Shader::setData(Program* program, const GLchar* property, MaterialValueType type, void* value)
{
	switch (type)
	{
		case Int:
			SendUniform(program, property, static_cast<int*>(value));
			break;
		case Float:
			SendUniform(program, property, static_cast<float*>(value));
			break;
		case Matrix4x4:
			SendUniform(program, property, static_cast<glm::mat4*>(value));
			break;
	}
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
