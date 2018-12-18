#pragma once
#include "Scene.h"

namespace Application
{
	namespace Scenes
	{
		class MeshScene : public Engine::Components::Scene
		{
		private:
			float t;
			std::vector<glm::vec3> P;
			int direction = 1;
			int n = 2;
			int nChoosek(unsigned n, unsigned k);
		public:
			void Load(Engine::BaseEngine* engine) override;
			void Unload(Engine::BaseEngine* engine) override;
			void FrameUpdate(Engine::BaseEngine* engine) override;
		};
	}
}



