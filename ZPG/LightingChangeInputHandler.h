#pragma once
#include "BaseInputHandler.h"

namespace Application {
	namespace Input {
		namespace Handlers
		{
			class LightingChangeInputHandler : public Engine::Components::BaseInputHandler
			{
			public:
				bool HandleKeys(Engine::BaseEngine* engine, Engine::Components::Window* window, Engine::Components::Scene* scene, Generic::Dictionary<short, bool>& keys, int keysActive) override;
			private:
				Engine::Components::Light* _selectedLight = nullptr;
			};
		}
	}
}
