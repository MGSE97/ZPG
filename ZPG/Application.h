#pragma once
#include "Dictionary.h"
#include <string>
#include "BaseEngine.h"

namespace Application
{
	class Application
	{
	public:
		~Application();
		static Application* GetIntance();
		Application* Init();
		Generic::Dictionary<std::string, Engine::BaseEngine*>* Engines;
	private:
		Application();
		static Application _instance;
		void RegisterEngines();
	};
}