#include <cstdlib>
#include <cstdio>
#include "Window.h"
#include <glm/mat4x2.hpp>
#include <glm/ext/quaternion_trigonometric.inl>
#include <glm/ext/matrix_transform.inl>
#include <ostream>

Engine::Components::Window::Window(int width, int height,const char* title, float speed, int swapInterval)
{
	Speed = speed;
	Width = width;
	Height = height;
	Title = title;
	SwapInterval = swapInterval;
	//OnUpdate += Sharp::EventHandler::Bind(&_update, *this);
}

Engine::Components::Window* Engine::Components::Window::Show()
{
	//Init GLFW
	/*if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}*/

	_window = glfwCreateWindow(Width, Height, Title, NULL, NULL);
	if (!_window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(_window);
	glfwSwapInterval(SwapInterval);
	glfwGetFramebufferSize(_window, &_width, &_height);
	_ratio = _width / (float)_height;
	glViewport(0, 0, _width, _height);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	return this;
}
/*
Engine::Components::Window* Engine::Components::Window::Run(glm::mat4 M)
{
	_angle = 0.f;
	while (!glfwWindowShouldClose(_window))
	{
		// Translate to point
		auto m = glm::translate(M, glm::vec3(0.0f, 0.5f, 0.0f));
		// Rotation
		m = glm::rotate(m, _angle, glm::vec3(0.0f, 0.0f, 1.0f));
		// Translate back
		m = glm::translate(m, glm::vec3(0.0f, -0.5f, 0.0f));
		_update(m);
		_angle += 0.001f*Speed;
	}
	return this;
}*/

Engine::Components::Window* Engine::Components::Window::Info(std::ostream& stream)
{
	// get version info
	stream << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	stream << "Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
	stream << "Vendor " << glGetString(GL_VENDOR) << std::endl;
	stream << "Renderer " << glGetString(GL_RENDERER) << std::endl;
	stream << "GLSL " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	stream << "Using GLFW " << major << "." << minor << "." << revision << std::endl;
	stream << "W, H, R: " << _width << ", " << _height << ", " << _ratio << std::endl;
	return this;
}

GLFWwindow* Engine::Components::Window::Get()
{
	return _window;
}
/*
Engine::Components::Window* Engine::Components::Window::SetProgram(Graphics::Program* program)
{
	ShaderProgram = program;
	return this;
}

Engine::Components::Window* Engine::Components::Window::SetObject(Objects::VertexObject* object)
{
	Object = object;
	return this;
}*/

Engine::Components::Window::~Window()
{
	glfwDestroyWindow(_window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

/*void Engine::Components::Window::_update(glm::mat4 M)
{
	if (ShaderProgram == NULL || Object == NULL)
		return;
	// clear color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(*ShaderProgram->Get());
	/*ShaderProgram->Shaders[0]->SendUniform(ShaderProgram, "modelMatrix", M);
	ShaderProgram->Shaders[1]->SendUniform(ShaderProgram, "color", _angle-(long)_angle);*/
	/*glBindVertexArray(Object->VAO->Get());

	// draw triangles
	glDrawArrays(GL_TRIANGLES, Object->VAO->StartArrayIndex, Object->VAO->Dimensions); //mode,first,count
	// update other events like input handling
	glfwPollEvents();
	// put the stuff we’ve been drawing onto the display
	glfwSwapBuffers(_window);
}*/
