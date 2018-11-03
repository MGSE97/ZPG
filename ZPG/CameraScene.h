#pragma once
#include "Scene.h"
namespace Application
{
	namespace Scenes
	{
		class CameraScene : public Engine::Components::Scene
		{
		public:
			CameraScene();
			~CameraScene();
			void Load(Engine::BaseEngine* engine) override;
			void FrameUpdate(Engine::BaseEngine* engine) override;
		private:
			glm::mat4* modelMatrix;
			float* angle;
			float* color;
		};
	}
}

