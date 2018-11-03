#include "ZPGEngine.h"
#include <iostream>
#include "Object.h"
#include "TriangleScene.h"

const char* vertex_shader =
"#version 330\n"
"uniform mat4 modelMatrix;"
"layout(location=0) in vec3 vp;"
"void main () {"
" gl_Position = modelMatrix * vec4 (vp, 1.0);"
"}";

const char* fragment_shader =
"#version 330\n"
"uniform float color;"
"out vec4 frag_colour;"
"void main () {"
"     frag_colour = vec4 (color, 1.0-color, 0.0, 1.0);"
"}";

Application::Engines::ZPGEngine* Application::Engines::ZPGEngine::Init(std::FILE* errorStream)
{
	BaseEngine::Init(errorStream);

	Windows->Add("zpg", (new ::Engine::Components::Window(800, 600, "ZPG", 100.0f))
		->Show()
		->Info(std::cout)
	);


	Shaders->Add("vertex", new ::Engine::Components::Shader(GL_VERTEX_SHADER, vertex_shader));
	Shaders->Add("fragment", new ::Engine::Components::Shader(GL_FRAGMENT_SHADER, fragment_shader));

	Programs->Add("shader", (new ::Engine::Components::Program())->AddShaders(Shaders));

	Scenes->Add((Engine::Components::Scene*) new Scenes::TriangleScene());

	for (auto it = Objects->begin(); it != Objects->end(); ++it)

	SetActiveScene();

	M = glm::mat4(1.0f);
	angle = 0.0f;
	return this;
}

void Application::Engines::ZPGEngine::Update(::Engine::Components::Window* window)
{
	for(auto it = Objects->begin(); it != Objects->end(); ++it)
	{
		/*ShaderProgram->Shaders[0]->SendUniform(ShaderProgram, "modelMatrix", M);
		ShaderProgram->Shaders[1]->SendUniform(ShaderProgram, "color", _angle-(long)_angle);*/
		auto object = it->second;
		//Handle Objects
		object->Program->Use();
		object->Program->Shaders->Get("vertex")->SendUniform(object->Program, "modelMatrix", M);
		object->Program->Shaders->Get("fragment")->SendUniform(object->Program, "color", angle - (long)angle);
		object->Draw();
		angle += 0.1f;
	}
}
