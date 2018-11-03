#pragma once
#include "IInputHandler.h"
#include <glm/gtc/quaternion.hpp>

namespace Application
{
	namespace Input
	{
		namespace Handlers
		{
			class CameraInputHandler : public Engine::Components::IInputHandler
			{
			private:
				glm::vec2 _lastMousePosition;
				float _pitch;
				float _yaw;
			public:
				CameraInputHandler();
				~CameraInputHandler();
				bool HandleKeys(Engine::BaseEngine* engine, Engine::Components::Window* window, Engine::Components::Scene* scene, Generic::Dictionary<short,bool>& keys, int keysActive) override;
				bool HandleMouse(Engine::BaseEngine* engine, Engine::Components::Window* window, Engine::Components::Scene* scene, double x, double y, Generic::Dictionary<short, bool>& keys, int keysActive) override;
			};
		}
	}
}


