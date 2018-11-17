#pragma once
#include "Scene.h"


namespace Application
{
	namespace Scenes
	{
		class PlaneScene : public Engine::Components::Scene
		{
		public:
			PlaneScene();
			~PlaneScene();
			void Load(Engine::BaseEngine* engine) override;
			void Unload(Engine::BaseEngine* engine) override;
		};
	}
}
