#pragma once
#include "Scene.h"
namespace Application
{
	namespace Scenes
	{
		class TriangleScene : public Engine::Components::Scene
		{
		public:
			TriangleScene();
			~TriangleScene();
			void Load(Engine::BaseEngine* engine) override;
			void FrameUpdate(Engine::BaseEngine* engine) override;
		private:
			glm::mat4* modelMatrix;
			float* angle;
			float* color;
		};
	}
}

