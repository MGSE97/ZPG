#pragma once
#include "Scene.h"

namespace Application
{
	namespace Scenes
	{
		class SphereScene : public Engine::Components::Scene
		{
		public:
			SphereScene();
			~SphereScene();
			void Load(Engine::BaseEngine* engine) override;
			void FrameUpdate(Engine::BaseEngine* engine) override;
		};
	}
}

