#pragma once
#include "BaseEngine.h"

namespace Application
{
	namespace Engines
	{
		class ZPGEngine : Engine::BaseEngine
		{
		public:
			ZPGEngine* Init(std::FILE* errorStream = stderr) override;
			void Update(::Engine::Components::Window* window) override;
		private:
			glm::mat4 M;
			float angle;
		};
	}
}

