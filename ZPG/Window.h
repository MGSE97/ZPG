#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Program.h"
#include "VertexObject.h"
#include <glm/mat4x2.hpp>

namespace Engine
{
	namespace Components
	{
		class Window
		{
		public:
			Window(int width, int height, const char* title, float speed = 10.0f, int swapInterval = 1);
			Window* Show();
			//Window* Run(glm::mat4 M);
			Window* Info(std::ostream& stream);
			GLFWwindow* Get();
			/*Window* SetProgram(Graphics::Program* program);
			Window* SetObject(Objects::VertexObject* object);*/
			~Window();
			float Speed;
			int Width;
			int Height;
			const char* Title;
			int SwapInterval;
			/*Graphics::Program* ShaderProgram;
			Objects::VertexObject* Object;*/
		private:
			GLFWwindow* _window;
			float _ratio;
			int _width;
			int _height;
			float _angle;
			//void _update(glm::mat4 M);
		};
	}
}

