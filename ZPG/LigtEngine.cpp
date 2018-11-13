#include "LigtEngine.h"
#include "TriangleScene.h"
#include <iostream>
#include <glm/ext/matrix_clip_space.hpp> 
#include "SphereScene.h"
#include <windows.h>
#include "CameraInputHandler.h"
#include "Assets.h"
#include "LightingChangeInputHandler.h"

Application::Engines::LightEngine* Application::Engines::LightEngine::Init(std::FILE* errorStream)
{
	BaseEngine::Init(errorStream);

	const char* vertex_shader =
		"#version 400\n"
		"layout(location=0) in vec3 vertexPos;"
		"layout(location=1) in vec3 normal;"
		"uniform mat4 modelMatrix;"
		"uniform mat4 viewMatrix;"
		"uniform mat4 projectionMatrix;"
		"out vec3 worldPos;"
		"out vec3 normVec;"
		"out vec3 lightVec;"
		"out vec3 eyeVec;"
		"void main () {"
			"gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4 (vertexPos, 1.0);"
			"vec3 vertexPosWorld = (modelMatrix * vec4(vertexPos, 1.0)).xyz;"
			"normVec = normalize(transpose(inverse(mat3(modelMatrix))) * normal);"
			"lightVec = normalize(vec3(0.0, 0.0, 0.0) - vertexPosWorld);"
			"worldPos = vertexPosWorld;"
			///"eyeVec = normalize(cameraPos - vertexPosWorld); "
		"}";

	//const char* fragment_shader =
	//	"#version 330 core"
	//	"out vec4 FragColor;"
	//	"uniform float color;"

	//	"in vec3 normVec;"
	//	"in vec3 lightVec;"
	//	"in vec3 eyeVec;"

	//	"void main()"
	//	"{"
	//		"vec3 lightAmbient = vec3(1.0);"
	//		"vec3 lightDiffuse = vec3(0.0, 1.0, 1.0);"
	//		"vec3 lightSpecular = vec3(1.0, 0.0, 1.0);"
	//		// ambient
	//		"float ambientStrength = 0.1;"
	//		"vec3 ambient = ambientStrength * lightAmbient;"

	//		// diffuse 
	//		"float diff = max(dot(normVec, lightVec), 0.0);"
	//		"vec3 diffuse = diff * lightDiffuse;"

	//		"vec3 result = (ambient + diffuse) * color;"
	//		"FragColor = vec4(result, 1.0);"
	//	"}";

	const char* fragment_shader =
		"#version 330\n"
		"uniform vec4 color;"
		"out vec4 frag_colour;"

		"in vec3 normVec;"
		"in vec3 lightVec;"
		"in vec3 eyeVec;"
		"in vec3 worldPos;"
		"void main () {"
			"float ambientStrength = 0.2;"
			"vec3 lightAmbient = vec3(1.0, 1.0, 1.0);"
			"vec3 lightDiffuse = vec3(0.0, 1.0, 1.0);"
			"vec3 lightSpecular = vec3(1.0, 0.0, 1.0);"
			"vec3 ambient = lightAmbient * ambientStrength;"
			//diffuse part
			"float dotDiff = max(dot(normVec, lightVec), 0.0);"
			"vec3 diffuse = dotDiff * lightDiffuse;"
			//specular part
			"vec3 reflVector = reflect(-lightVec, normVec);"
			"float dotSpec = pow(max(dot(reflVector, eyeVec), 0.0), 256);"
			"vec3 specular = dotSpec * lightSpecular;"
			"frag_colour = vec4(ambient + diffuse + specular, 1.0)*color;"
			//"frag_colour = vec4(worldPos, 1.0);"
			//"frag_colour = vec4(normVec, 1.0);"
			//"frag_colour = vec4(ambient*color, 1.0);"
			//"frag_colour = vec4(diffuse*color, 1.0);"
			//"frag_colour = vec4(specular*color, 1.0);"
			//"frag_colour = vec4 (color, 1.0-color, 0.0, 1.0);"
		"}";

	//M = glm::mat4(1.0f);
	angle = 0.0f;

	/*ambientStrength = 0.2f;
	diffuseStrength = 0.5f;
	specularStrength = 0.5f;
	specularSize = 16;
	ambientColor = glm::vec3(1.0, 1.0, 1.0);
	diffuseColor = glm::vec3(1.0, 1.0, 1.0);
	specularColor = glm::vec3(1.0, 1.0, 1.0);*/

	auto window = (new ::Engine::Components::Window(1024, 768, "ZPG - Camera", 100.0f))
		->Show()
		->Info(std::cout);
	Windows->Add("zpg", window);

	auto* vertex = new Engine::Components::Graphics::Shader(GL_VERTEX_SHADER, Assets::ShadersVertex + "Light.glsl");
	auto* fragment = new Engine::Components::Graphics::Shader(GL_FRAGMENT_SHADER, Assets::ShadersFragment + "Light.glsl");
	Shaders->Add("vertex", vertex);
	Shaders->Add("fragment", fragment);

	Programs->Add("basic", (new Engine::Components::Graphics::Program())->AddShaders(Shaders));

	Scenes->Add("triangle", new Scenes::TriangleScene());
	Scenes->Add("sphere", new Scenes::SphereScene());

	InputHandlers->Add(new Input::Handlers::LightingChangeInputHandler());
	InputHandlers->Add(new Input::Handlers::CameraInputHandler());

	SetActiveScene(Scenes->Get("sphere"));

	auto* lc = new Engine::Components::Graphics::LightConfiguration();
	lc->AmbientStrength = 1.f;
	lc->DiffuseStrength = 1.f;
	lc->SpecularStrength = 1.f;
	ActiveScene->Lights->Add("light" , new Engine::Components::Light(Programs->Get("basic"), glm::vec3(0, 0, 0), glm::vec4(1), lc));

	ActiveScene->Cameras->Add("main", (new Engine::Components::Camera())
		//->SetPosition(new glm::vec3(2.5f, 2.5f, 2.f))
		->SetPosition(new glm::vec3(0.f, 0.f, -4.f))
		->SetDirection(new glm::vec3(0.f, 0.f, 0.f))
		->SetUp(new glm::vec3(0.f, 1.f, 0.f)));
	ActiveScene->Cameras->First()->Projection = new glm::mat4(glm::perspective(glm::radians(45.f), (float)window->Width / (float)window->Height, 0.1f, 100.0f));

	ActiveScene->BeginLoad(this);
	std::string lightPrefix = "light_";
	if (ActiveScene != nullptr && ActiveScene->Lights != nullptr && !ActiveScene->Lights->empty())
		for (auto& it : *ActiveScene->Lights)
		{
			ActiveScene->Objects->Add(lightPrefix + it.first, it.second);
		}
	if (ActiveScene != nullptr && ActiveScene->Objects != nullptr && !ActiveScene->Objects->empty())
		for (auto& it : *ActiveScene->Objects)
		{
			/*it.second->Material
				->Add(vertex, "viewMatrix", ActiveScene->ActiveCamera->Value)
				->Add(vertex, "projectionMatrix", ActiveScene->ActiveCamera->Projection)
				->Add(vertex, "cameraPos", ActiveScene->ActiveCamera->Position);*/
			
			if (ActiveScene != nullptr && ActiveScene->Lights != nullptr && !ActiveScene->Lights->empty() && 
				strncmp(it.first.c_str(), lightPrefix.c_str(), lightPrefix.size()) != 0)
				for (auto& light : *ActiveScene->Lights)
				{
					light.second->Use(it.second->Material);
				}
		}
	return this;
}

void Application::Engines::LightEngine::Update(::Engine::Components::Window* window)
{
	//std::cout << "PS: " << specularSize << "\nSS: " << specularStrength << "\nDS: " << diffuseStrength << "\nAS: " << ambientStrength << "\nLP: " << ActiveScene->Lights->First()->Configuration.GlobalStrength << std::endl;
	
	if (ActiveScene != nullptr && ActiveScene->Objects != nullptr && !ActiveScene->Objects->empty())
		for (auto& it : *ActiveScene->Objects)
		{
			/*auto _fi = glm::radians(90.f*(MouseX / window->Height));
			auto _psi = glm::radians(90.f*(MouseY / window->Width));

			std::cout << "FI:  " << _fi << "\nPSI: " << _psi << "\nObject: " << it.first << std::endl;
			*/
			//ActiveScene->Cameras->First()->SetDirection(new glm::vec3(cos(_fi), sin(_fi), cos(_psi)));
			std::cout << "Object: " << it.first << (it.second->Clicked?" (CLICKED)":"                ") << std::endl;
			auto object = it.second;
			object->Draw();
			
			angle += 0.1f;
		}
}
