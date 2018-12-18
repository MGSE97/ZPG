#include "BaseEngine.h"
#include <windows.h>
#include "IInputHandler.h"
#include <glm/ext/matrix_projection.hpp>

Engine::BaseEngine::BaseEngine()
{
	Windows = new Generic::Dictionary<std::string, Components::Window*>();
	Shaders = new Generic::Dictionary<std::string, Components::Graphics::Shader*>();
	Scenes = new Generic::Dictionary<std::string, Components::Scene*>();
	Keys = *(new Generic::Dictionary<short, bool>());
	MouseKeys = *(new Generic::Dictionary<short, bool>());
	InputHandlers = new Generic::Collection<Components::IInputHandler*>();
	_init = false;
	_errorStream = stderr;
	ActiveScene = nullptr;
}

Engine::BaseEngine::~BaseEngine()
{
	Windows->clear();
	Shaders->clear();
	Scenes->clear();
	delete Windows;
	delete Shaders;
	delete Scenes;
}

Engine::BaseEngine* Engine::BaseEngine::Init(std::FILE* errorStream)
{
	fprintf(errorStream, "Engine initialization started\n");
	fprintf(errorStream, "Engine.Init %f s\t> Inicialization started\n", glfwGetTime());
	_init = true;
	_errorStream = errorStream;
	fprintf(errorStream, "Engine.Init %f s\t> Inicialization GLFW started\n", glfwGetTime());
	InitGLFW();
	fprintf(errorStream, "Engine.Init %f s\t> Inicialization GLFW complete\n", glfwGetTime());
	/*if(_init)
		for(auto window: *Windows)
			glfwSetKeyCallback(window.second->Get(), WindowKeyCallback);*/
	// Create keys
	for (short i = 1; i < 512; i++)
		Keys.Add(i, false);
	//Disable VSync
	glfwSwapInterval(0);
	fprintf(errorStream, "Engine.Init %f s\t> Inicialization complete\n", glfwGetTime());
	return this;
}

bool Engine::BaseEngine::InitSuccess()
{
	return _init;
}

Engine::BaseEngine* Engine::BaseEngine::Dispose()
{
	glfwTerminate();
	return this;
}

void Engine::BaseEngine::UpdateBegin(Components::Window* window)
{
	// Scene
	ActiveScene->BeginLoad(this);

	// Buffers
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glDepthFunc(GL_LESS);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Input
	short mouseKeysActive = 0;
	glfwGetCursorPos(window->Get(), &MouseX, &MouseY);
	for(short i = 0; i < 8; i++)
	{
		const int state = glfwGetMouseButton(window->Get(), i);
		auto value = MouseKeys[i];
		// flip state
		if (state == GLFW_PRESS && !value)
			MouseKeys.Add(i, true);
		else if (state == GLFW_RELEASE && value)
			MouseKeys.Add(i, false);
		if (MouseKeys[i])
			mouseKeysActive++;
	}
	short keysActive = 0;
	for (short i = 1; i < 512; i++)
	{
		const int state = glfwGetKey(window->Get(), i);
		auto value = Keys[i];
		// flip state
		if (state == GLFW_PRESS && !value)
			Keys.Add(i, true);
		else if (state == GLFW_RELEASE && value)
			Keys.Add(i, false);
		if (Keys[i])
			keysActive++;
	}
	bool handleKeys = true,
		 handleMouse = true;
	for (auto handler : *InputHandlers)
	{
		if(handleKeys)
			handleKeys = handler->HandleKeys(this, window, ActiveScene, Keys, keysActive);
		if(handleMouse)
			handleMouse = handler->HandleMouse(this, window, ActiveScene, MouseX, MouseY, MouseKeys, mouseKeysActive);
		if(!handleKeys && !handleMouse)
			break;
	}
	//SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 40, 0 });
	int lightCount = ActiveScene->Lights->size();
	for (auto it : *Shaders)
		if (it.second != nullptr)
		{
			ActiveScene->ActiveCamera->Use(it.second);
			it.second->SendUniform("lightCount", &lightCount);
		}
}

void Engine::BaseEngine::Update(Components::Window* window)
{
}

void Engine::BaseEngine::UpdateEnd(Components::Window* window)
{
	// update other events like input handling
	glfwPollEvents();
	// put the stuff we’ve been drawing onto the display
	glfwSwapBuffers(window->Get());

	ActiveScene->FrameUpdate(this);

	// ToggleClickedObjects
	const int calculatedY = (int)window->Height - MouseY - 1;
	//GLubyte color[4];
	GLuint index;
	GLfloat depth;
	//glReadPixels(MouseX, calculatedY, 1, 1, GL_RGBA2, GL_UNSIGNED_BYTE, color);
	//glReadPixels(MouseX, MouseY, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
	glReadPixels(MouseX, calculatedY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
	glReadPixels(MouseX, calculatedY, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
	glm::vec3 screenX = glm::vec3(MouseX, calculatedY, depth);
	glm::mat4* view = ActiveScene->ActiveCamera->Value;
	glm::mat4* projection = ActiveScene->ActiveCamera->Projection;

	glm::vec4 viewPort = glm::vec4(0, 0, (float)window->Width, (float)window->Height);
	WorldPosition = glm::unProject(screenX, *view, *projection, viewPort);
	WorldObjectId = index;

	/*fprintf(_errorStream, "WP:\t%f, %f, %f\n", WorldPosition.x, WorldPosition.y, WorldPosition.z);
	fprintf(_errorStream, "WO:\t%d\t\t\n", index);*/
	
}

void Engine::BaseEngine::Start()
{
	//system("cls");
	fprintf(_errorStream, "Engine.Start %f s\t> Started\n", glfwGetTime());
	UpdateInternal();
}

void Engine::BaseEngine::SetActiveScene(Components::Scene* scene)
{
	if (scene == nullptr && !Scenes->empty())
		ActiveScene = Scenes->begin()->second;
	else
		ActiveScene = scene;		
}

/*void Engine::BaseEngine::WindowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Components::Window* activeWindow = nullptr;
	for (auto win : *Windows)
		if (win.second->Get() == window)
		{
			activeWindow = win.second;
			break;
		}

	if(activeWindow != nullptr)
	{
		for (auto handler : *InputHandlers)
			handler->HandleKeys(this, activeWindow, ActiveScene, Key);
	}
}*/

Engine::BaseEngine* Engine::BaseEngine::InitGLFW()
{
	if (!glfwInit()) {
		fprintf(_errorStream, "ERROR: could not start GLFW3\n");
		_init = false;
	}
	return this;
}

void Engine::BaseEngine::UpdateInternal()
{
	//fprintf(_errorStream, "Engine started\n");
	while(true)
	{
		for (auto window = Windows->begin(); window != Windows->end(); ++window)
			if(glfwWindowShouldClose(window->second->Get()))
			{
				delete window->second;
				Windows->erase(window->first);
			}
			else
			{
				UpdateBegin(window->second);
				Update(window->second);
				UpdateEnd(window->second);
			}
	}
}

