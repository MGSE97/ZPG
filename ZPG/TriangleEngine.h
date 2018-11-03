#pragma once
#include "BaseEngine.h"

namespace Application
{
	namespace Engines
	{
		class TriangleEngine : public Engine::BaseEngine
		{
		public:
			TriangleEngine* Init(std::FILE* errorStream = stderr) override;
			void Update(::Engine::Components::Window* window) override;
		private:
			glm::mat4 M;
			float angle;
		};
	}
}

