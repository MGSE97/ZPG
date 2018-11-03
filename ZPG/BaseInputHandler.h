#pragma once
#include "IInputHandler.h"

namespace Engine
{
	namespace Components
	{
		class BaseInputHandler : public Engine::Components::IInputHandler
		{
		public:
			BaseInputHandler() = default;
			~BaseInputHandler() = default;
			virtual bool HandleKeys(BaseEngine* engine, Window* window, Scene* scene, Generic::Dictionary<short, bool>& keys, int keysActive) override;
			virtual bool HandleMouse(BaseEngine* engine, Window* window, Scene* scene, double x, double y, Generic::Dictionary<short, bool>& keys, int keysActive) override;
		};
	}
}

