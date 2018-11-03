#pragma once
#include "BaseEngine.h"

namespace Application
{
	namespace Engines
	{
		class CameraEngine : public Engine::BaseEngine
		{
		public:
			CameraEngine* Init(std::FILE* errorStream = stderr) override;
			void Update(::Engine::Components::Window* window) override;
		private:
			glm::mat4 M;
			float angle;
		};
	}
}

