#pragma once
#include <ostream>
#include "Dictionary.h"
#include "Program.h"
#include "Window.h"
#include "Scene.h"
#include "IInputHandler.h"

namespace Engine
{
	class BaseEngine
	{
	public:
		BaseEngine();
		~BaseEngine();
		virtual BaseEngine* Init(std::FILE* errorStream = stderr);
		bool InitSuccess();
		BaseEngine* Dispose();

		virtual void UpdateBegin(Components::Window* window);
		virtual void Update(Components::Window* window);
		virtual void UpdateEnd(Components::Window* window);
		virtual void Start();
		virtual void SetActiveScene(Components::Scene* scene = nullptr);
		//virtual void WindowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

		Generic::Dictionary<std::string, Components::Window*>* Windows;
		Generic::Dictionary<std::string, Components::Graphics::Program*>* Programs;
		Generic::Dictionary<std::string, Components::Graphics::Shader*>* Shaders;
		Generic::Dictionary<std::string, Components::Scene*>* Scenes;
		Generic::Collection<Components::IInputHandler*>* InputHandlers;
		Generic::Dictionary<short, bool> Keys;
		Generic::Dictionary<short, bool> MouseKeys;
		Components::Scene* ActiveScene;
		double MouseX;
		double MouseY;
		glm::vec3 WorldPosition;
		glm::vec4 WorldObject;

	private:
		BaseEngine* InitGLFW();
		std::FILE* _errorStream;
		bool _init;
		void UpdateInternal();
	};
}

