#include "Program.h"
#include "Shader.h"
#include "Collection.h"
#include "Dictionary.h"
#include "MaterialValue.h"


Engine::Components::Graphics::Program::Program()
{
	_program = glCreateProgram();
	_linked = false;
	Shaders = new Generic::Dictionary<std::string,Shader*>();
}


Engine::Components::Graphics::Program::~Program()
{
	Shaders->clear();
	delete Shaders;
}

Engine::Components::Graphics::Program* Engine::Components::Graphics::Program::AddShader(std::string key,Shader* shader)
{
	Shaders->Add(key, shader);
	glAttachShader(_program, *shader->Get());
	return this;
}

Engine::Components::Graphics::Program* Engine::Components::Graphics::Program::AddShaders(Generic::Dictionary<std::string,Shader*>* shaders)
{
	/*for (Shader* shader : *shaders)
		AddShader(shader);*/
	for (auto it = shaders->begin(); it != shaders->end(); ++it)
		AddShader(it->first, it->second);
	return this;
}

Engine::Components::Graphics::Program* Engine::Components::Graphics::Program::Link()
{
	glLinkProgram(_program);
	_linked = CheckLink();
	return this;
}

Engine::Components::Graphics::Program* Engine::Components::Graphics::Program::Use()
{
	glUseProgram(*Get());
	return this;
}

GLuint* Engine::Components::Graphics::Program::Get()
{
	if(!_linked)
		Link();
	return &_program;
}

bool Engine::Components::Graphics::Program::CheckLink()
{
	GLint status;
	glGetProgramiv(_program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(_program, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
		return false;
	}
	return true;
}

