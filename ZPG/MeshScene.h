#pragma once
#include "Scene.h"

namespace Application
{
	namespace Scenes
	{
		class MeshScene : public Engine::Components::Scene
		{
		public:
			void Load(Engine::BaseEngine* engine) override;
			void Unload(Engine::BaseEngine* engine) override;
		};
	}
}



